cmake_minimum_required(VERSION 3.10)

project(mugboid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set (MUGENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/mugengine/include)
set(MUGBOID_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(MUGBOID_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MUGBOID_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${MUGBOID_INSTALL_INCLUDE_DIR})
add_subdirectory(src)
add_subdirectory(../mugengine mugengine)
