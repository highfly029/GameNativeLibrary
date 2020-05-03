project(detour_cpp CXX C) # 这里可以不写CXX和C，但不能只写一个，否则只会编译指定语言
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  #设置c++的编译选项
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")  #设置c的编译选项
aux_source_directory(. dir_src) #指定路径，并产生变量${dir_src}
add_executable(main ${dir_src}) #指定代码目录