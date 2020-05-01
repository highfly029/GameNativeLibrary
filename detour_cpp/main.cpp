#include <iostream>
#include "SoloMesh.h"

int main(int argc, char* argv[]) {
	printf("begin!\n");
	SoloMesh tool;
	tool.LoadNavMesh("solo_navmesh.bin");
	// float sp[3], ep[3];
	// while (scanf("%f%f%f%f%f%f", &sp[0], &sp[1], &sp[2], &ep[0], &ep[1], &ep[2]) != EOF) {
	// 	tool.FindPath(sp, ep);
	// }
	float start[3];
	float end[3];
	start[0] = -500.0f;
	start[1] = 1.0f;
	start[2] = 1.0f;

	end[0] = 0.0f;
	end[1] = 1.0f;
	end[2] = 200.0f;
	tool.findPathFollow(start, end);
	printf("test 1!\n");

	tool.findPathStraight(start, end);

	tool.findPathSliced(start, end);

	float r1[3];
	float r2[3];
	r1[0] = -499.0f;
	r1[1] = 1.0f;
	r1[2] = 1.0f;

	r2[0] = -400.0f;
	r2[1] = 1.0f;
	r2[2] = 400.0f;
	tool.raycast(r1, r2);
	return 0;
}
