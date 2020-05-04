#pragma once

#include <stdio.h>
#include <string.h>
#include <fstream>
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "DetourNavMeshBuilder.h"
#include "DetourCommon.h"
#include "DetourTileCache.h"
#include "DetourTileCacheBuilder.h"
#include "InputGeom.h"
#include "fastlz.h"

class TempObstacle
{
	dtNavMesh* m_navMesh;
	dtNavMeshQuery* m_navQuery;
	dtQueryFilter m_filter;
	float m_polyPickExt[3];

	static const int MAX_POLYS = 256;
	static const int MAX_SMOOTH = 2048;

	float m_spos[3];
	float m_epos[3];
	dtPolyRef m_startRef;
	dtPolyRef m_endRef;
	dtPolyRef m_polys[MAX_POLYS];
	dtPolyRef m_parent[MAX_POLYS];
	int m_npolys;
	int m_nsmoothPath;
	float m_smoothPath[MAX_SMOOTH * 3];

	int m_nstraightPath;
	float m_straightPath[MAX_POLYS*3];
	unsigned char m_straightPathFlags[MAX_POLYS];
	dtPolyRef m_straightPathPolys[MAX_POLYS];
	int m_straightPathOptions;

	float m_hitPos[3];

	bool m_isPrint;

///////////TmpObstacle///////////
	struct LinearAllocator* m_talloc;
	struct FastLZCompressor* m_tcomp;
	struct MeshProcess* m_tmproc;

	class dtTileCache* m_tileCache;

public:
	TempObstacle();
	virtual ~TempObstacle();

	void setPrint(bool isPrint);
	void LoadMeshFile(const char* file_name);
	void LoadNavMesh(const char* file_name);
	void findPathFollow(float sp[3],float ep[3]);
	void findPathStraight(float sp[3],float ep[3]);
	void findPathSliced(float sp[3],float ep[3]);
	bool raycast(float sp[3],float ep[3]);

	void update();
	int addObstacle(float *p, float radius, float height);
	int addBoxObstacle(float* bmin, float* bmax);
	int addBoxObstacle(float* center, float* halfExtents, float yRadians);
	bool removeOneObstacle(int idx);
	void removeAllObstacle();
};