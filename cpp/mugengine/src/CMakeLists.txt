cmake_minimum_required(VERSION 3.10)
project(mugengine C CXX)

set(SOURCE_FILES
    mugengine.hpp
    mugengine.cpp
)

add_library(mugengine SHARED STATIC ${SOURCE_FILES})

install(TARGETS mugengine DESTINATION ${MUGENGINE_INSTALL_LIB_DIR})
# install(FILES division.h DESTINATION ${MUGENGINE_INSTALL_INCLUDE_DIR})