cmake_minimum_required(VERSION 3.13)

project(mugboid C CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set (MUGENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/mugengine/include)
set(MUGBOID_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(MUGBOID_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MUGBOID_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${MUGBOID_INSTALL_INCLUDE_DIR})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
        src/main.cpp
)

add_executable(mugboid ${SOURCE_FILES})
target_link_libraries(mugboid mugengine glad glfw)
file(COPY res DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
)
add_dependencies(mugboid copy_assets)

add_subdirectory(test)
