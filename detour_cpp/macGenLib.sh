#/usr/bin/bash

clang -c fastlz.c
clang++ -std=c++11 -c common/Source/ChunkyTriMesh.cpp -I common/Include
clang++ -std=c++11 -c Detour/Source/DetourAlloc.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourAssert.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourCommon.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourNavMesh.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourNavMeshBuilder.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourNavMeshQuery.cpp -I Detour/Include
clang++ -std=c++11 -c Detour/Source/DetourNode.cpp -I Detour/Include
clang++ -std=c++11 -c DetourTileCache/Source/DetourTileCache.cpp -I DetourTileCache/Include -I Detour/Include
clang++ -std=c++11 -c DetourTileCache/Source/DetourTileCacheBuilder.cpp -I DetourTileCache/Include -I Detour/Include
clang++ -std=c++11 -c common/Source/MeshLoaderObj.cpp -I common/Include
clang++ -std=c++11 -c SoloMesh.cpp -I common/Include -I Detour/Include
clang++ -std=c++11 -c TempObstacle.cpp -I common/Include -I Detour/Include -I DetourTileCache/Include

clang++ -std=c++11 -c main.cpp -I common/Include -I Detour/Include -I DetourTileCache/Include

# clang++ -o main fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
#                 DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o main.o

clang++ -dynamiclib -o libGameNativeLibrary.dylib com_highfly029_GameNativeLibrary.cpp fastlz.o ChunkyTriMesh.o DetourAlloc.o DetourAssert.o DetourCommon.o DetourNavMesh.o DetourNavMeshBuilder.o DetourNavMeshQuery.o \
        DetourNode.o DetourTileCache.o DetourTileCacheBuilder.o MeshLoaderObj.o SoloMesh.o TempObstacle.o \
        -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin -I common/Include -I Detour/Include -I DetourTileCache/Include

rm -rf *.o
