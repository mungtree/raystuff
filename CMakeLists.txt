cmake_minimum_required(VERSION 3.10)

# Project Information
project(RayStuff C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Define the executable name in a variable
set(EXECUTABLE_NAME "raystuff")

# Find raylib (can either use installed version or custom one)
# Change the raylib path accordingly if you have it in a custom location
# set(RAYLIB_PATH ${CMAKE_SOURCE_DIR}/lib/raylib)
# Include raylib directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define source files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(SOURCES
  ${SOURCE_DIR}/main.c
  ${LIB_DIR}/glad.c
)

# Create executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link raylib library
target_link_libraries(${EXECUTABLE_NAME} raylib GL glfw rt)

# Ensure the compiler finds raylib's headers and libraries
# target_include_directories(raylib_example PRIVATE ${RAYLIB_PATH}/src)

# Set platform-specific settings
if(UNIX)
    # For Linux
    target_link_libraries(${EXECUTABLE_NAME} m X11 pthread dl)
elseif(WIN32)
    # For Windows
    target_link_libraries(raylib_example opengl32 gdi32 winuser)
endif()

# RESOURCES
add_custom_command(
  TARGET ${EXECUTABLE_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)


