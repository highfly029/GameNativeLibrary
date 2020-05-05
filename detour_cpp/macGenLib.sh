#/usr/bin/bash

clang -c fastlz.c
clang++ -std=c++11 -c ChunkyTriMesh.cpp
clang++ -std=c++11 -c DetourAlloc.cpp
clang++ -std=c++11 -c DetourAssert.cpp
clang++ -std=c++11 -c DetourCommon.cpp
clang++ -std=c++11 -c DetourNavMesh.cpp
clang++ -std=c++11 -c DetourNavMeshBuilder.cpp
clang++ -std=c++11 -c DetourNavMeshQuery.cpp
clang++ -std=c++11 -c DetourNode.cpp
clang++ -std=c++11 -c DetourTileCache.cpp
clang++ -std=c++11 -c DetourTileCacheBuilder.cpp
clang++ -std=c++11 -c MeshLoaderObj.cpp
clang++ -std=c++11 -c SoloMesh.cpp
clang++ -std=c++11 -c TempObstacle.cpp

clang++ -std=c++11 -c main.cpp

# clang++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

clang++ -dynamiclib -o libGameNativeLibrary.dylib com_highfly029_GameNativeLibrary.cpp fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin

rm -rf *.o
