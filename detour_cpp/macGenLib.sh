#/usr/bin/bash

clang -c fastlz.c
clang++ -std=c++17 -stdlib=libc++ -c ChunkyTriMesh.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourAlloc.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourAssert.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourCommon.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourNavMesh.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourNavMeshBuilder.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourNavMeshQuery.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourNode.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourTileCache.cpp
clang++ -std=c++17 -stdlib=libc++ -c DetourTileCacheBuilder.cpp
clang++ -std=c++17 -stdlib=libc++ -c MeshLoaderObj.cpp
clang++ -std=c++17 -stdlib=libc++ -c SoloMesh.cpp
clang++ -std=c++17 -stdlib=libc++ -c TempObstacle.cpp

clang++ -std=c++17 -stdlib=libc++ -c main.cpp

# clang++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

clang++ -dynamiclib -o libGameNativeLibrary.dylib fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin

rm -rf *.o
