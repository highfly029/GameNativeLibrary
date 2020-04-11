#/usr/bin/bash


RECAST_SRC=../GameNativeLibrary/GameNativeLibrary.cpp \
	../GameNativeLibrary/NavMesh.cpp \
	../GameNativeLibrary/Source/DetourAlloc.cpp \
	../GameNativeLibrary/Source/DetourCommon.cpp \
	../GameNativeLibrary/Source/DetourCrowd.cpp \
	../GameNativeLibrary/Source/DetourLocalBoundary.cpp \
	../GameNativeLibrary/Source/DetourNavMeshBuilder.cpp \
	../GameNativeLibrary/Source/DetourNavMesh.cpp \
	../GameNativeLibrary/Source/DetourNavMeshQuery.cpp \
	../GameNativeLibrary/Source/DetourNode.cpp \
	../GameNativeLibrary/Source/DetourObstacleAvoidance.cpp \
	../GameNativeLibrary/Source/DetourPathCorridor.cpp \
	../GameNativeLibrary/Source/DetourPathQueue.cpp \
	../GameNativeLibrary/Source/DetourProximityGrid.cpp \
	../GameNativeLibrary/Source/DetourTileCacheBuilder.cpp \
	../GameNativeLibrary/Source/DetourTileCache.cpp \
	../GameNativeLibrary/Source/RecastAlloc.cpp \
	../GameNativeLibrary/Source/RecastArea.cpp \
	../GameNativeLibrary/Source/RecastContour.cpp \
	../GameNativeLibrary/Source/Recast.cpp \
	../GameNativeLibrary/Source/RecastFilter.cpp \
	../GameNativeLibrary/Source/RecastLayers.cpp \
	../GameNativeLibrary/Source/RecastMesh.cpp \
	../GameNativeLibrary/Source/RecastMeshDetail.cpp \
	../GameNativeLibrary/Source/RecastRasterization.cpp \
	../GameNativeLibrary/Source/RecastRegion.cpp

g++ -dynamiclib -o GameNativeLibrary.jnilib RECAST_SRC -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin
