cmake_minimum_required(VERSION 3.13)

project(mugengine)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(MUGENGINE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(MUGENGINE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MUGENGINE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${MUGENGINE_INSTALL_INCLUDE_DIR})
include_directories(glad/include)


# not target clauses to avoid being imported twice
if (NOT TARGET glad)
    add_subdirectory(glad/)
endif()

if (NOT TARGET mugengine)
    add_subdirectory(src)
endif()

if (NOT TARGET mugengine_tests)
    add_subdirectory(test)
endif()