#/usr/bin/bash

gcc -c fastlz.c
g++ -std=c++11 -c ChunkyTriMesh.cpp
g++ -std=c++11 -c DetourAlloc.cpp
g++ -std=c++11 -c DetourAssert.cpp
g++ -std=c++11 -c DetourCommon.cpp
g++ -std=c++11 -c DetourNavMesh.cpp
g++ -std=c++11 -c DetourNavMeshBuilder.cpp
g++ -std=c++11 -c DetourNavMeshQuery.cpp
g++ -std=c++11 -c DetourNode.cpp
g++ -std=c++11 -c DetourTileCache.cpp
g++ -std=c++11 -c DetourTileCacheBuilder.cpp
g++ -std=c++11 -c MeshLoaderObj.cpp
g++ -std=c++11 -c SoloMesh.cpp
g++ -std=c++11 -c TempObstacle.cpp

g++ -std=c++11 -c main.cpp

# g++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

g++ -dynamiclib -o libGameNativeLibrary.dylib com_highfly029_GameNativeLibrary.cpp fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin

rm -rf *.o
