cmake_minimum_required(VERSION 3.10)
project(mugtree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")

add_subdirectory(mugengine)
add_subdirectory(boid)