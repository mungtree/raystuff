cmake_minimum_required(VERSION 3.13)

project(mugexample)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(EXAMPLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(EXAMPLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXAMPLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(../mugengine mugengine)
