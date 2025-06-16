cmake_minimum_required(VERSION 3.13)
project(mugrdp_tests)

set(SOURCE_FILES main.cpp src/example.cpp)

add_executable(mugrdp_tests ${SOURCE_FILES})
target_link_libraries(mugrdp_tests mugengine gtest)
# install(TARGETS mugengine_tests DESTINATION bin)