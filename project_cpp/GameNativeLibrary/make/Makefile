PLATS = linux
.PHONY : linux all clean 

CC = g++

GSHARED = -fPIC --shared -lrt -Wl,-E
CFLAGS = -g -O2 -Wall -msse -msse2 -ffast-math  -mfpmath=sse

RECAST_SRC = ../GameNativeLibrary/GameNativeLibrary.cpp \
	../GameNativeLibrary/NavMesh.cpp \
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

linux : GameNativeLibrary.so
		$(MAKE) all PLAT=$@ GSHARED="$(GSHARED)"

all : GameNativeLibrary.so

GameNativeLibrary.so : $(RECAST_SRC)
	$(CC) $(CFLAGS) $(GSHARED) $^ -o $@ -I../GameNativeLibrary/ -I../GameNativeLibrary/Include -I/usr/java/jdk1.8.0_181-amd64/include -I/usr/java/jdk1.8.0_181-amd64/include/linux

