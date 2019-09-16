#!/bin/bash

rm -rf ./GameNativeLibrary.so

g++ -g -O2 -Wall -msse -msse2 -ffast-math  -mfpmath=sse -fPIC --shared -lrt -Wl,-E -I../GameNativeLibrary -o ./GameNativeLibrary.so -I/usr/java/jdk1.8.0_181-amd64/include -I/usr/java/jdk1.8.0_181-amd64/include/linux
