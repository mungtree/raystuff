cmake_minimum_required(VERSION 3.13)
project(mugtree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0")

set(MUGCOMMON_INSTALL_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/mug-lib)
set(MUGCOMMON_INSTALL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/mug-include)
add_subdirectory(mugengine)
add_subdirectory(boid)
add_subdirectory(example)
