#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import os
import subprocess
import sys
import shutil

if __name__ == '__main__':
    os.chdir("../detour_cpp/")
    genLibCmd = "./macGenLib.sh"
    ret = subprocess.call(genLibCmd, shell=True)
    if (ret != 0):
        print("genLibCmd failed!")

    os.chdir("../project_java/")

    shutil.copyfile("../detour_cpp/libGameNativeLibrary.dylib", "src/main/resources/libGameNativeLibrary.dylib")
    shutil.copyfile("../detour_cpp/libGameNativeLibrary.so", "src/main/resources/libGameNativeLibrary.so")

    ret = os.system("mvn -DskipTests clean compile")

    if (ret != 0):
        print("mvn failed")
    
    cmd = "jar cvf GameNativeLibrary.jar -C target/classes ."
    print(cmd)
    ret = subprocess.call(cmd, shell=True)
    if (ret != 0):
        print("gen jar failed")

    cmd = "mvn install:install-file -Dfile=GameNativeLibrary.jar -DgroupId=com.highfly029 -DartifactId=GameNativeLibrary -Dversion=1.0.0 -Dpackaging=jar"
    ret = subprocess.call(cmd, shell=True)
    if (ret != 0):
        print("mvn install failed")

    os.system("pause")
