cmake_minimum_required(VERSION 3.13)
project(mugengine_tests)

set(SOURCE_FILES main.cpp src/example.cpp)

add_executable(mugengine_tests ${SOURCE_FILES})
target_link_libraries(mugengine_tests mugengine gtest)
# install(TARGETS mugengine_tests DESTINATION bin)