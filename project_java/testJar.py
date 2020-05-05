#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import os
import subprocess
import sys
import shutil

if __name__ == '__main__':
    cmd = "java -cp GameNativeLibrary.jar com.highfly029.GameNativeLibrary"
    print(cmd)
    ret = subprocess.call(cmd, shell=True)
    if (ret != 0):
        print("gen jar failed")

    os.system("pause")
