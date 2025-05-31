cmake_minimum_required(VERSION 3.10)
project(mugboid C CXX)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_FILES
        main.cpp
)

add_executable(mugboid ${SOURCE_FILES})
target_link_libraries(mugboid mugengine)
# install(TARGETS mugboid DESTINATION ${MUGENGINE_INSTALL_BIN_DIR})
