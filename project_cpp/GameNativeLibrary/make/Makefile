PLATS = linux
.PHONY : linux all clean 

CC = g++

GSHARED = -fPIC --shared -lrt -Wl,-E
CFLAGS = -g -O2 -Wall -msse -msse2 -ffast-math  -mfpmath=sse

RECAST_SRC = ../GameNativeLibrary/dllmain.cpp \
	../GameNativeLibrary/GameNativeLibrary.cpp \
	../GameNativeLibrary/stdafx.cpp \


linux : GameNativeLibrary.so
	$(MAKE) all PLAT=$@ GSHARED="$(GSHARED)"

all : GameNativeLibrary.so

GameNativeLibrary.so : $(RECAST_SRC)
	$(CC) $(CFLAGS) $(GSHARED) $^ -o $@ -I../GameNativeLibrary

