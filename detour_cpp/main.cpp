#include <iostream>
#include "SoloMesh.h"
#include "TempObstacle.h"

void testSolo() {
	SoloMesh tool;
	tool.LoadNavMesh("solo_navmesh.bin");
	printf("hello SoloMesh!\n");
	float start[3];
	float end[3];
	start[0] = 1.0f;
	start[1] = 1.0f;
	start[2] = 1.0f;

	end[0] = 500.0f;
	end[1] = 1.0f;
	end[2] = 200.0f;
	// tool.findPathFollow(start, end);

	tool.findPathStraight(start, end);

	float r1[3];
	float r2[3];
	r1[0] = 6.6f;
	r1[1] = 0.0f;
	r1[2] = 1.7f;

	r2[0] = 400.0f;
	r2[1] = 0.0f;
	r2[2] = 400.0f;
	tool.raycast(r1, r2);
}

void testTempObstacle() {
	TempObstacle tool;
	tool.LoadNavMesh("all_tiles_tilecache.bin");
	printf("hello TempObstacle!\n");
	float start[3];
	float end[3];
	start[0] = 1.0f;
	start[1] = 1.0f;
	start[2] = 1.0f;

	end[0] = 500.0f;
	end[1] = 1.0f;
	end[2] = 200.0f;
	// tool.findPathFollow(start, end);

	tool.findPathStraight(start, end);

	float r1[3];
	float r2[3];
	r1[0] = 6.6f;
	r1[1] = 0.0f;
	r1[2] = 1.7f;

	r2[0] = 400.0f;
	r2[1] = 0.0f;
	r2[2] = 400.0f;
	tool.raycast(r1, r2);
}

int main(int argc, char* argv[]) {
	printf("begin!\n");
	testSolo();
	testTempObstacle();
	return 0;
}
