cmake_minimum_required(VERSION 3.6)
project(kc_clustergen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp clustergen.cpp clustergen.h)
add_executable(clustergen ${SOURCE_FILES})