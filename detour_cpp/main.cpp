#include "SoloMesh.h"
#include "TempObstacle.h"
#include <map>
#include <string>
//linux
#include <unistd.h>


using namespace std;

void testSolo() {
	map<string, SoloMesh*> soloMeshMap;
	SoloMesh* tool = new SoloMesh();
	string name = "abc";
	// map<string, SoloMesh*>::iterator iter; 
	if (soloMeshMap.find(name) != soloMeshMap.end())
	{
		printf("map 存在 abc\n");
		return;
	} else
	{
		printf("map 不存在 abc\n");
		soloMeshMap[name] = tool;
	}

	string name2 = string("abc");

	SoloMesh* tool2 = soloMeshMap.find(name2)->second;

	if (tool2)
	{
		printf("abc 插入成功\n");
	}
	if (tool == tool2)
	{
		printf("abc 完全相等\n");
	}
	
	
	
	
	tool->setPrint(true);
	tool->loadNavMesh("solo_navmesh.bin");
	printf("hello SoloMesh!\n");
	float start[3];
	float end[3];
	start[0] = -1.0f;
	start[1] = 1.0f;
	start[2] = 1.0f;

	end[0] = -500.0f;
	end[1] = 1.0f;
	end[2] = 200.0f;
	// tool.findPathFollow(start, end);

	std::vector<Vector3D> outPaths;
	tool->findPathStraight(start, end, outPaths);
	std::vector<Vector3D>::iterator iter = outPaths.begin();
	printf("output begin\n");
	for (; iter != outPaths.end(); ++iter)
	{
		float x = iter->x;
		float y = iter->y;
		float z = iter->z;
		printf("(pos x:%f y:%f z:%f) ", x, y, z);	
	}
	printf("\noutput end\n");

	float r1[3];
	float r2[3];
	r1[0] = -1.0f;
	r1[1] = 1.0f;
	r1[2] = 1.0f;

	r2[0] = -200.0f;
	r2[1] = 1.0f;
	r2[2] = 400.0f;

	r1[0] = 10.0f;
	r1[1] = 0.0f;
	r1[2] = 10.0f;

	r2[0] = 10.0f;
	r2[1] = 0.0f;
	r2[2] = 15.0f;

	float hitPoint[3];
	tool->raycast(r1, r2, hitPoint);
	printf("hitPoint x=%f,y=%f,z=%f", hitPoint[0], hitPoint[1], hitPoint[2]);
}

void testTempObstacle() {
	TempObstacle tool;
	tool.setPrint(true);
	tool.loadNavMesh("all_tiles_tilecache.bin");
	printf("hello TempObstacle!\n");
	float start[3];
	float end[3];
	start[0] = -1.0f;
	start[1] = 1.0f;
	start[2] = 1.0f;

	end[0] = -500.0f;
	end[1] = 1.0f;
	end[2] = 200.0f;
	// tool.findPathFollow(start, end);

	std::vector<Vector3D> outPaths;
	tool.findPathStraight(start, end, outPaths);

	float r1[3];
	float r2[3];
	r1[0] = -1.0f;
	r1[1] = 1.0f;
	r1[2] = 1.0f;

	r2[0] = -200.0f;
	r2[1] = 1.0f;
	r2[2] = 400.0f;
	float hitPoint[3];
	tool.raycast(r1, r2, hitPoint);

	printf("动态阻挡测试 \n");
	r1[0] = -10.0f;
	r1[1] = 1.0f;
	r1[2] = 350.0f;

	r2[0] = -400.0f;
	r2[1] = 1.0f;
	r2[2] = 350.0f;
	tool.raycast(r1, r2, hitPoint);

	//增加动态阻挡
	float boxMin[3] = {-50.0f, 0.0f, 340.0f};
	float boxMax[3];
	float width = 14.0f;
	float length = 14.0f;
	int len = 3;
	int array[len];
	for (int i = 0; i < len; i++)
	{
		boxMax[0] = boxMin[0] + length;
		boxMax[1] = boxMin[1] + 10;
		boxMax[2] = boxMin[2] + width;
		int idx = tool.addBoxObstacle(boxMin, boxMax);
		array[i] = idx;
		tool.update();
		bool isHit = tool.raycast(r1, r2, hitPoint);
		printf("test add i=%d, idx=%d, isHit=%d,minX=%.3f,minZ=%.3f,maxX=%.3f,maxZ=%.3f\n", i, idx, isHit,
		boxMin[0], boxMin[2], boxMax[0], boxMax[2]);

		boxMin[0] = boxMax[0];
		boxMin[1] = boxMax[1];
		boxMin[2] = boxMax[2];
	}
	printf("\n\n=========================\n\n");
	//删除单个动态阻挡
	for (int i = 0; i < len; i++)
	{
		int idx = array[i];
		bool result = tool.removeOneObstacle(idx);
		tool.update();
		bool isHit = tool.raycast(r1, r2, hitPoint);
		printf("test remove i=%d, idx=%d, result=%d, isHit=%d\n", i, idx, result, isHit);
	}

	// boxMin[0] = -50.0f;
	// boxMin[1] = 0.0f;
	// boxMin[2] = 340.0f;
	// for (int i = 0; i < len; i++)
	// {
	// 	boxMax[0] = boxMin[0] + length;
	// 	boxMax[1] = boxMin[1] + 10;
	// 	boxMax[2] = boxMin[2] + width;
	// 	int idx = tool.addBoxObstacle(boxMin, boxMax);
	// 	array[i] = idx;
	// 	tool.update();
	// 	bool isHit = tool.raycast(r1, r2);
	// 	printf("test add i=%d, idx=%d, isHit=%d,minX=%.3f,minZ=%.3f,maxX=%.3f,maxZ=%.3f\n", i, idx, isHit,
	// 	boxMin[0], boxMin[2], boxMax[0], boxMax[2]);

	// 	boxMin[0] = boxMax[0];
	// 	boxMin[1] = boxMax[1];
	// 	boxMin[2] = boxMax[2];
	// }

	//删除全部动态阻挡
	// tool.setPrint(true);
	// tool.removeAllObstacle();
	// tool.update();
	// tool.raycast(r1, r2);
	
}

int main(int argc, char* argv[]) {
	printf("begin!\n");
	testSolo();
	// while (true)
	// {
	// 	sleep(1);
	// 	testTempObstacle();
	// }
	
	
	return 0;
}
