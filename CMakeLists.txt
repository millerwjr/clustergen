cmake_minimum_required(VERSION 3.6)
project(kc_clustergen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp kc_clustergen.h kc_clustergen.cpp)
add_executable(kc_clustergen ${SOURCE_FILES})