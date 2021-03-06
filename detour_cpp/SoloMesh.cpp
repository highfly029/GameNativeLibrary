#include <stdio.h>
#include <string.h>
#include <fstream>
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "DetourCommon.h"
#include "SoloMesh.h"
#include "common.h"
#include <vector>

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK = 0x01,		// Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM = 0x02,		// Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR = 0x04,		// Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP = 0x08,		// Ability to jump.
	SAMPLE_POLYFLAGS_DISABLED = 0x10,		// Disabled polygon
	SAMPLE_POLYFLAGS_ALL = 0xffff	// All abilities.
};

template<class T> inline T rcMin(T a, T b) { return a < b ? a : b; }

template<class T> inline T rcMax(T a, T b) { return a > b ? a : b; }

inline bool inRange(const float* v1, const float* v2, const float r, const float h)
{
	const float dx = v2[0] - v1[0];
	const float dy = v2[1] - v1[1];
	const float dz = v2[2] - v1[2];
	return (dx*dx + dz*dz) < r*r && fabsf(dy) < h;
}

static bool getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
	const float minTargetDist,
	const dtPolyRef* path, const int pathSize,
	float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
	float* outPoints = 0, int* outPointCount = 0)
{
	// Find steer target.
	static const int MAX_STEER_POINTS = 3;
	float steerPath[MAX_STEER_POINTS * 3];
	unsigned char steerPathFlags[MAX_STEER_POINTS];
	dtPolyRef steerPathPolys[MAX_STEER_POINTS];
	int nsteerPath = 0;
	navQuery->findStraightPath(startPos, endPos, path, pathSize,
		steerPath, steerPathFlags, steerPathPolys, &nsteerPath, MAX_STEER_POINTS);
	if (!nsteerPath)
		return false;

	if (outPoints && outPointCount)
	{
		*outPointCount = nsteerPath;
		for (int i = 0; i < nsteerPath; ++i)
			dtVcopy(&outPoints[i * 3], &steerPath[i * 3]);
	}


	// Find vertex far enough to steer to.
	int ns = 0;
	while (ns < nsteerPath)
	{
		// Stop at Off-Mesh link or when point is further than slop away.
		if ((steerPathFlags[ns] & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ||
			!inRange(&steerPath[ns * 3], startPos, minTargetDist, 1000.0f))
			break;
		ns++;
	}
	// Failed to find good point to steer to.
	if (ns >= nsteerPath)
		return false;

	dtVcopy(steerPos, &steerPath[ns * 3]);
	steerPos[1] = startPos[1];
	steerPosFlag = steerPathFlags[ns];
	steerPosRef = steerPathPolys[ns];

	return true;
}

static int fixupCorridor(dtPolyRef* path, const int npath, const int maxPath,
	const dtPolyRef* visited, const int nvisited)
{
	int furthestPath = -1;
	int furthestVisited = -1;

	// Find furthest common polygon.
	for (int i = npath - 1; i >= 0; --i)
	{
		bool found = false;
		for (int j = nvisited - 1; j >= 0; --j)
		{
			if (path[i] == visited[j])
			{
				furthestPath = i;
				furthestVisited = j;
				found = true;
			}
		}
		if (found)
			break;
	}

	// If no intersection found just return current path. 
	if (furthestPath == -1 || furthestVisited == -1)
		return npath;

	// Concatenate paths.	

	// Adjust beginning of the buffer to include the visited.
	const int req = nvisited - furthestVisited;
	const int orig = rcMin(furthestPath + 1, npath);
	int size = rcMax(0, npath - orig);
	if (req + size > maxPath)
		size = maxPath - req;
	if (size)
		memmove(path + req, path + orig, size * sizeof(dtPolyRef));

	// Store visited
	for (int i = 0; i < req; ++i)
		path[i] = visited[(nvisited - 1) - i];

	return req + size;
}

// This function checks if the path has a small U-turn, that is,
// a polygon further in the path is adjacent to the first polygon
// in the path. If that happens, a shortcut is taken.
// This can happen if the target (T) location is at tile boundary,
// and we're (S) approaching it parallel to the tile edge.
// The choice at the vertex can be arbitrary, 
//  +---+---+
//  |:::|:::|
//  +-S-+-T-+
//  |:::|   | <-- the step can end up in here, resulting U-turn path.
//  +---+---+
static int fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery)
{
	if (npath < 3)
		return npath;

	// Get connected polygons
	static const int maxNeis = 16;
	dtPolyRef neis[maxNeis];
	int nneis = 0;

	const dtMeshTile* tile = 0;
	const dtPoly* poly = 0;
	if (dtStatusFailed(navQuery->getAttachedNavMesh()->getTileAndPolyByRef(path[0], &tile, &poly)))
		return npath;

	for (unsigned int k = poly->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
	{
		const dtLink* link = &tile->links[k];
		if (link->ref != 0)
		{
			if (nneis < maxNeis)
				neis[nneis++] = link->ref;
		}
	}

	// If any of the neighbour polygons is within the next few polygons
	// in the path, short cut to that polygon directly.
	static const int maxLookAhead = 6;
	int cut = 0;
	for (int i = dtMin(maxLookAhead, npath) - 1; i > 1 && cut == 0; i--) {
		for (int j = 0; j < nneis; j++)
		{
			if (path[i] == neis[j]) {
				cut = i;
				break;
			}
		}
	}
	if (cut > 1)
	{
		int offset = cut - 1;
		npath -= offset;
		for (int i = 1; i < npath; i++)
			path[i] = path[i + offset];
	}

	return npath;
}

SoloMesh::~SoloMesh()
{
	if (m_isPrint)
	{
		printf("release SoloMesh\n");
	}
	dtFreeNavMesh(m_navMesh);
	dtFreeNavMeshQuery(m_navQuery);
	m_startRef = 0;
	m_endRef = 0;
	m_npolys = 0;
	m_nsmoothPath = 0;
	m_nstraightPath = 0;
}

SoloMesh::SoloMesh() :m_navMesh(0), m_navQuery(0), m_isPrint(false)
{
	if (m_isPrint)
	{
		printf("new SoloMesh\n");	
	}
	m_navQuery = dtAllocNavMeshQuery();

	m_filter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL ^ SAMPLE_POLYFLAGS_DISABLED);
	m_filter.setExcludeFlags(0);

	m_polyPickExt[0] = 2;
	m_polyPickExt[1] = 4;
	m_polyPickExt[2] = 2;
}

void SoloMesh::setPrint(bool isPrint)
{
	m_isPrint = isPrint;
}

dtNavMesh* SoloMesh::loadMeshFile(const char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	if (!fp)
	{
		printf("loadMeshFile file cant open %s!\n", file_name);
		return 0;
	}
	

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		printf("loadMeshFile fread failed!\n");
		return 0;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		printf("loadMeshFile magic failed!\n");
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		printf("loadMeshFile version failed!\n");
		return 0;
	}

	m_navMesh = dtAllocNavMesh();
	if (!m_navMesh)
	{
		fclose(fp);
		printf("loadMeshFile mesh is null!\n");
		return 0;
	}
	dtStatus status = m_navMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		printf("loadMeshFile mesh init failed!\n");
		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
		{
			fclose(fp);
			printf("loadMeshFile Read tiles failed!\n");
			return 0;
		}

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
		{
			dtFree(data);
			fclose(fp);
			printf("loadMeshFile Read tiles failed!\n");
			return 0;
		}

		m_navMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return m_navMesh;
}

bool SoloMesh::loadNavMesh(const char* file_name) 
{
	if (!file_name) {
		printf("loadNavMesh error fileName!\n");
		return false;
	}

	dtFreeNavMesh(m_navMesh);
	m_navMesh = loadMeshFile(file_name);
	if (!m_navMesh)
	{
		printf("loadMeshFile failed!\n");
		return false;
	}
	
	dtStatus status = m_navQuery->init(m_navMesh, 2048);
	if (dtStatusSucceed(status))
	{
		return true;
	} else {
		return false;
	}
}

int SoloMesh::findPathFollow(float sp[3], float ep[3], std::vector<Vector3D>& paths) 
{
	if (m_isPrint)
	{
		printf("findPathFollow\n");
	}	
	for (int i = 0; i < 3; i++) 
	{
		m_spos[i] = sp[i];
		m_epos[i] = ep[i];
	}

	m_navQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, 0);
	m_navQuery->findNearestPoly(m_epos, m_polyPickExt, &m_filter, &m_endRef, 0);

	if (!m_startRef)
	{
		return START_REF_NULL;
	}
	if (!m_endRef)
	{
		return END_REF_NULL;
	}
	
	m_navQuery->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, m_polys, &m_npolys, MAX_POLYS);

	m_nsmoothPath = 0;

	if (m_npolys)
	{
		// Iterate over the path to find smooth path on the detail mesh surface.
		dtPolyRef polys[MAX_POLYS];
		memcpy(polys, m_polys, sizeof(dtPolyRef)*m_npolys);
		int npolys = m_npolys;

		float iterPos[3], targetPos[3];
		m_navQuery->closestPointOnPoly(m_startRef, m_spos, iterPos, 0);
		m_navQuery->closestPointOnPoly(polys[npolys - 1], m_epos, targetPos, 0);

		static const float STEP_SIZE = 0.5f;
		static const float SLOP = 0.01f;

		m_nsmoothPath = 0;

		dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
		m_nsmoothPath++;

		// Move towards target a small advancement at a time until target reached or
		// when ran out of memory to store the path.
		while (npolys && m_nsmoothPath < MAX_SMOOTH)
		{
			// Find location to steer towards.
			float steerPos[3];
			unsigned char steerPosFlag;
			dtPolyRef steerPosRef;

			if (!getSteerTarget(m_navQuery, iterPos, targetPos, SLOP,
				polys, npolys, steerPos, steerPosFlag, steerPosRef))
				break;

			bool endOfPath = (steerPosFlag & DT_STRAIGHTPATH_END) ? true : false;
			bool offMeshConnection = (steerPosFlag & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ? true : false;

			// Find movement delta.
			float delta[3], len;
			dtVsub(delta, steerPos, iterPos);
			len = dtMathSqrtf(dtVdot(delta, delta));
			// If the steer target is end of path or off-mesh link, do not move past the location.
			if ((endOfPath || offMeshConnection) && len < STEP_SIZE)
				len = 1;
			else
				len = STEP_SIZE / len;
			float moveTgt[3];
			dtVmad(moveTgt, iterPos, delta, len);

			// Move
			float result[3];
			dtPolyRef visited[16];
			int nvisited = 0;
			m_navQuery->moveAlongSurface(polys[0], iterPos, moveTgt, &m_filter,
				result, visited, &nvisited, 16);

			npolys = fixupCorridor(polys, npolys, MAX_POLYS, visited, nvisited);
			npolys = fixupShortcuts(polys, npolys, m_navQuery);

			float h = 0;
			m_navQuery->getPolyHeight(polys[0], result, &h);
			result[1] = h;
			dtVcopy(iterPos, result);

			// Handle end of path and off-mesh links when close enough.
			if (endOfPath && inRange(iterPos, steerPos, SLOP, 1.0f))
			{
				// Reached end of path.
				dtVcopy(iterPos, targetPos);
				if (m_nsmoothPath < MAX_SMOOTH)
				{
					dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
					m_nsmoothPath++;
				}
				break;
			}
			else if (offMeshConnection && inRange(iterPos, steerPos, SLOP, 1.0f))
			{
				// Reached off-mesh connection.
				float startPos[3], endPos[3];

				// Advance the path up to and over the off-mesh connection.
				dtPolyRef prevRef = 0, polyRef = polys[0];
				int npos = 0;
				while (npos < npolys && polyRef != steerPosRef)
				{
					prevRef = polyRef;
					polyRef = polys[npos];
					npos++;
				}
				for (int i = npos; i < npolys; ++i)
					polys[i - npos] = polys[i];
				npolys -= npos;

				// Handle the connection.
				dtStatus status = m_navMesh->getOffMeshConnectionPolyEndPoints(prevRef, polyRef, startPos, endPos);
				if (dtStatusSucceed(status))
				{
					if (m_nsmoothPath < MAX_SMOOTH)
					{
						dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
						m_nsmoothPath++;
						// Hack to make the dotted path not visible during off-mesh connection.
						if (m_nsmoothPath & 1)
						{
							dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
							m_nsmoothPath++;
						}
					}
					// Move position at the other side of the off-mesh link.
					dtVcopy(iterPos, endPos);
					float eh = 0.0f;
					m_navQuery->getPolyHeight(polys[0], iterPos, &eh);
					iterPos[1] = eh;
				}
			}

			// Store results.
			if (m_nsmoothPath < MAX_SMOOTH)
			{
				dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
				m_nsmoothPath++;
			}
		}

		if (m_nsmoothPath >= MAX_SMOOTH)
		{
			printf("m_nsmoothPath=%d isMax\n", m_nsmoothPath);
		}

		if (m_nsmoothPath)
		{
			int num = 0;
			Vector3D vector3D;
			//打印路径点
			for (int i = 0; i < m_nsmoothPath; ++i)
			{
				float x = m_smoothPath[i * 3];
				float y = m_smoothPath[i * 3 + 1];
				float z = m_smoothPath[i * 3 + 2];

				vector3D.x = x;
				vector3D.y = y;
				vector3D.z = z;
				paths.push_back(vector3D);
				if (m_isPrint)
				{
					printf("(pos x:%f y:%f z:%f) ", x, y, z);	
				}
				num++;
			}
			if (m_isPrint)
			{
				printf("\n");
			}
			return num;
		}
	}
	return UNKNOWN_FAIL;
}

int SoloMesh::findPathStraight(float sp[3],float ep[3], std::vector<Vector3D>& paths) 
{
	if (m_isPrint)
	{
		printf("SoloMesh findPathStraight\n");	
	}
	for (int i = 0; i < 3; i++) 
	{
		m_spos[i] = sp[i];
		m_epos[i] = ep[i];
	}

	m_navQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, 0);
	m_navQuery->findNearestPoly(m_epos, m_polyPickExt, &m_filter, &m_endRef, 0);

	if (!m_startRef)
	{
		return START_REF_NULL;
	}
	if (!m_endRef)
	{
		return END_REF_NULL;
	}

	m_navQuery->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, m_polys, &m_npolys, MAX_POLYS);
	m_nstraightPath = 0;
	if (m_npolys)
	{
		// In case of partial path, make sure the end point is clamped to the last polygon.
		float epos[3];
		dtVcopy(epos, m_epos);
		if (m_polys[m_npolys-1] != m_endRef)
			m_navQuery->closestPointOnPoly(m_polys[m_npolys-1], m_epos, epos, 0);
		
		m_navQuery->findStraightPath(m_spos, epos, m_polys, m_npolys,
										m_straightPath, m_straightPathFlags,
										m_straightPathPolys, &m_nstraightPath, MAX_POLYS, m_straightPathOptions);

		if (m_nstraightPath)
		{
			int num = 0;
			Vector3D vector3D;
			//打印路径点
			for (int i = 0; i < m_nstraightPath; ++i)
			{
				float x = m_straightPath[i * 3];
				float y = m_straightPath[i * 3 + 1];
				float z = m_straightPath[i * 3 + 2];
				vector3D.x = x;
				vector3D.y = y;
				vector3D.z = z;
				paths.push_back(vector3D);
				if (m_isPrint)
				{
					printf("(pos x:%f y:%f z:%f) ", x, y, z);	
				}
				num++;
			}
			if (m_isPrint)
			{
				printf("\n");	
			}
			return num;
		}							
	}
	return UNKNOWN_FAIL;
}

int SoloMesh::findPathSliced(float sp[3],float ep[3], std::vector<Vector3D>& paths) 
{
	printf("SoloMesh findPathSliced not support!\n");
	return UN_SUPPORT;
}

bool SoloMesh::raycast(float sp[3], float ep[3], float* hitPoint)
{
	bool result = false;
	for (int i = 0; i < 3; i++) 
	{
		m_spos[i] = sp[i];
		m_epos[i] = ep[i];
	}

	float hitNormal[3];
	memset(hitNormal,0,sizeof(hitNormal));

	m_navQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, 0);
	if (!m_startRef)
	{
		printf("raycast startRef is null\n");
	}
	float t = 0;
	m_npolys = 0;
	dtStatus status = m_navQuery->raycast(m_startRef, m_spos, m_epos, &m_filter, &t, hitNormal, m_polys, &m_npolys, MAX_POLYS);
	if (t > 1)
	{
		// No hit
		result = false;
	}
	else
	{
		// Hit
		dtVlerp(m_hitPos, m_spos, m_epos, t);
		result = true;
	}
	// Adjust height.
	if (m_npolys > 0)
	{
		float h = 0;
		m_navQuery->getPolyHeight(m_polys[m_npolys-1], m_hitPos, &h);
		m_hitPos[1] = h;
	}
	if (result && hitPoint)
	{
		hitPoint[0] = m_hitPos[0];
		hitPoint[1] = m_hitPos[1];
		hitPoint[2] = m_hitPos[2];
	}
	if (m_isPrint)
	{
		printf("raycast hit=%d, hitX=%f,hitY=%f,hitZ=%f\n", result, m_hitPos[0], m_hitPos[1], m_hitPos[2]);
	}
	return result;
}
