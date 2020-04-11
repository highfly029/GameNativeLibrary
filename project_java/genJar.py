#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import os
import subprocess
import sys

if __name__ == '__main__':
    ret = os.system("mvn -DskipTests clean compile")

    if (ret != 0):
        print("mvn failed")
    

    cmd = "jar cvf GameNativeLibrary.jar -C target/classes ."
    print(cmd)
    ret = subprocess.call(cmd, shell=True)

    os.system("pause")
