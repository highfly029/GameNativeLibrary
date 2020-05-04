cmake_minimum_required (VERSION 3.17)
project(detour_cpp CXX C) # 这里可以不写CXX和C，但不能只写一个，否则只会编译指定语言

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  #设置c++的编译选项
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")  #设置c的编译选项
include_directories($ENV{JAVA_HOME}/include $ENV{JAVA_HOME}/include/darwin)

aux_source_directory(. dir_src) #指定路径，并产生变量${dir_src}
add_library(recast SHARED ${dir_src})

