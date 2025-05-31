cmake_minimum_required(VERSION 3.13)
project(mugboid_tests)

set(SOURCE_FILES main.cpp src/example.cpp)

add_executable(mugboid_tests ${SOURCE_FILES})
target_link_libraries(mugboid_tests mugengine gtest)
# install(TARGETS mugengine_tests DESTINATION bin)