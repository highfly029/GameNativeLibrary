#/usr/bin/bash

gcc -c fastlz.c
g++ -std=c++11 -fPIC -c ChunkyTriMesh.cpp
g++ -std=c++11 -fPIC -c DetourAlloc.cpp
g++ -std=c++11 -fPIC -c DetourAssert.cpp
g++ -std=c++11 -fPIC -c DetourCommon.cpp
g++ -std=c++11 -fPIC -c DetourNavMesh.cpp
g++ -std=c++11 -fPIC -c DetourNavMeshBuilder.cpp
g++ -std=c++11 -fPIC -c DetourNavMeshQuery.cpp
g++ -std=c++11 -fPIC -c DetourNode.cpp
g++ -std=c++11 -fPIC -c DetourTileCache.cpp
g++ -std=c++11 -fPIC -c DetourTileCacheBuilder.cpp
g++ -std=c++11 -fPIC -c MeshLoaderObj.cpp
g++ -std=c++11 -fPIC -c SoloMesh.cpp
g++ -std=c++11 -fPIC -c TempObstacle.cpp

g++ -std=c++11 -fPIC -c main.cpp

# g++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

g++ -fPIC -shared -o libGameNativeLibrary.so com_highfly029_GameNativeLibrary.cpp fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -I/$JAVA_HOME/include -I/$JAVA_HOME/include/linux

rm -rf *.o
