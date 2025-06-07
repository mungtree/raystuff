cmake_minimum_required(VERSION 3.13)

project(mugexample C CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(MUGEXAMPLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(MUGEXAMPLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(MUGEXAMPLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${MUGEXAMPLE_INSTALL_INCLUDE_DIR})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
        src/main.cpp
)

add_executable(mugexample ${SOURCE_FILES})
target_link_libraries(mugexample mugengine glad glfw)
file(COPY res DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

    add_custom_target(copy_example_assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
    )
add_dependencies(mugexample copy_example_assets)

add_subdirectory(test)
