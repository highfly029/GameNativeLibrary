#pragma once

#include <stdio.h>
#include <string.h>
#include <fstream>
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "DetourCommon.h"
#include "common.h"
#include <vector>

class SoloMesh
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
	
public:
	SoloMesh();
	virtual ~SoloMesh();

	void setPrint(bool isPrint);
	dtNavMesh* loadMeshFile(const char* file_name);
	bool loadNavMesh(const char* file_name);
	
	int findPathFollow(float sp[3], float ep[3], std::vector<Vector3D>& paths);
	int findPathStraight(float sp[3], float ep[3], std::vector<Vector3D>& paths);
	int findPathSliced(float sp[3], float ep[3], std::vector<Vector3D>& paths);

	bool raycast(float sp[3], float ep[3], float* hitPoint);
};