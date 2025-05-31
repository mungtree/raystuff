cmake_minimum_required(VERSION 3.13)
project(mugengine C CXX)

set(INCLUDE_FILES
        mugengine.hpp
)
set(SOURCE_FILES
        ${INCLUDE_FILES}
        mugengine.cpp
)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)


add_library(mugengine SHARED STATIC ${SOURCE_FILES})
target_link_libraries(mugengine PRIVATE glfw glm::glm)
target_include_directories(mugengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS mugengine DESTINATION ${MUGENGINE_INSTALL_LIB_DIR})
install(TARGETS mugengine DESTINATION ${MUGCOMMON_INSTALL_LIB_DIR})


if (DEFINED MUGENGINE_INSTALL_INCLUDE_DIR)
    install(FILES ${INCLUDE_FILES} DESTINATION ${MUGENGINE_INSTALL_INCLUDE_DIR})
endif()
if (DEFINED MUGCOMMON_INSTALL_INCLUDE_DIR)
    install(FILES ${INCLUDE_FILES} DESTINATION ${MUGCOMMON_INSTALL_INCLUDE_DIR})
endif (DEFINED MUGCOMMON_INSTALL_INCLUDE_DIR)

# install(FILES division.h DESTINATION ${MUGENGINE_INSTALL_INCLUDE_DIR})