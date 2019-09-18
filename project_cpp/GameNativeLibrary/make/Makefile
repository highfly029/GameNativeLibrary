PLATS = linux
.PHONY : linux all clean 

CC = g++

GSHARED = -fPIC --shared -lrt -Wl,-E
CFLAGS = -g -O2 -Wall -msse -msse2 -ffast-math  -mfpmath=sse

RECAST_SRC = ../GameNativeLibrary/GameNativeLibrary.cpp \
	../GameNativeLibrary/NavMesh.cpp \
	

linux : GameNativeLibrary.so
		$(MAKE) all PLAT=$@ GSHARED="$(GSHARED)"

all : GameNativeLibrary.so

GameNativeLibrary.so : $(RECAST_SRC)
	$(CC) $(CFLAGS) $(GSHARED) $^ -o $@ -I../GameNativeLibrary/ -I../GameNativeLibrary/Include -I/usr/java/jdk1.8.0_181-amd64/include -I/usr/java/jdk1.8.0_181-amd64/include/linux

