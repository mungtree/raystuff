cmake_minimum_required(VERSION 3.13)
project(example_tests)

set(SOURCE_FILES main.cpp src/example.cpp)

add_executable(example_tests ${SOURCE_FILES})
target_link_libraries(example_tests mugengine gtest)
# install(TARGETS mugengine_tests DESTINATION bin)