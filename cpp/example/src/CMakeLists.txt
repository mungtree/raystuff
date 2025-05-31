cmake_minimum_required(VERSION 3.13)
project(mugexample C CXX)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_FILES
        main.cpp
)

add_executable(mugexample ${SOURCE_FILES})
target_link_libraries(mugexample mugengine glad glfw)
# install(TARGETS mugboid DESTINATION ${MUGENGINE_INSTALL_BIN_DIR})
