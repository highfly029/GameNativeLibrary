#/usr/bin/bash


SRC=main.cpp \
                SoloMesh.cpp \
                Detour/Source/DetourAlloc.cpp \
                Detour/Source/DetourAssert.cpp \
                Detour/Source/DetourCommon.cpp \
                Detour/Source/DetourNavMesh.cpp \
                Detour/Source/DetourNavMeshBuilder.cpp \
                Detour/Source/DetourNavMeshQuery.cpp \
                Detour/Source/DetourNode.cpp \
                DetourTileCache/Source/DetourTileCache.cpp \
                DetourTileCache/Source/DetourTileCacheBuilder.cpp \
                common/Source/ChunkyTriMesh.cpp \
                common/Source/fastlz.c \
                common/Source/InputGeom.cpp \
                common/Source/MeshLoaderObj.cpp \

g++ -dynamiclib -o GameNativeLibrary.jnilib SRC -framework JavaVM -I/$JAVA_HOME/include -I/$JAVA_HOME/include/darwin
