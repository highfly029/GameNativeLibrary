#/usr/bin/bash

gcc -c fastlz.c
g++ -std=c++17 -stdlib=libc++ -c ChunkyTriMesh.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourAlloc.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourAssert.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourCommon.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourNavMesh.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourNavMeshBuilder.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourNavMeshQuery.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourNode.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourTileCache.cpp
g++ -std=c++17 -stdlib=libc++ -c DetourTileCacheBuilder.cpp
g++ -std=c++17 -stdlib=libc++ -c MeshLoaderObj.cpp
g++ -std=c++17 -stdlib=libc++ -c SoloMesh.cpp
g++ -std=c++17 -stdlib=libc++ -c TempObstacle.cpp

g++ -std=c++17 -stdlib=libc++ -c main.cpp

# g++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

g++ -dynamiclib -o libGameNativeLibrary.dylib com_highfly029_GameNativeLibrary.cpp fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin

rm -rf *.o
