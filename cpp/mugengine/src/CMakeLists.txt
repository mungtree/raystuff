cmake_minimum_required(VERSION 3.13)
project(mugengine C CXX)

set(INCLUDE_FILES
        MugEngine.hpp
        util/MugLogger.hpp
        util/PairHelpers.h
        shaders/MugShader.hpp
        render/simple/SimpleTriangle.h
        render/simple/SimplePoint.h
        render/simple/InstancedTriangles.h
)
set(SOURCE_FILES
        ${INCLUDE_FILES}
        MugEngine.cpp
        util/MugLogger.cpp
        shaders/MugShader.cpp
        render/simple/SimpleTriangle.cpp
        render/simple/InstancedTriangles.cpp
)

set(EXTERNAL_LIBS
    glfw
    glm::glm
)


# External Deps
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Logger
find_package(spdlog QUIET)
if (spdlog_FOUND)
    message(STATUS "Using spdlog")
    list(APPEND EXTERNAL_LIBS spdlog::spdlog)
else()
    message(WARNING "spdlog not found, using fallback logging.")
endif()



# BUILD
add_library(mugengine SHARED STATIC ${SOURCE_FILES})
target_link_libraries(mugengine PRIVATE ${EXTERNAL_LIBS})
target_include_directories(mugengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (spdlog_FOUND)
    target_compile_definitions(mugengine PRIVATE USE_SPDLOG)
endif()


# INSTALL
install(TARGETS mugengine DESTINATION ${MUGENGINE_INSTALL_LIB_DIR})
install(TARGETS mugengine DESTINATION ${MUGCOMMON_INSTALL_LIB_DIR})

if (DEFINED MUGENGINE_INSTALL_INCLUDE_DIR)
    install(FILES ${INCLUDE_FILES} DESTINATION ${MUGENGINE_INSTALL_INCLUDE_DIR})
endif()
if (DEFINED MUGCOMMON_INSTALL_INCLUDE_DIR)
    install(FILES ${INCLUDE_FILES} DESTINATION ${MUGCOMMON_INSTALL_INCLUDE_DIR})
endif (DEFINED MUGCOMMON_INSTALL_INCLUDE_DIR)

# install(FILES division.h DESTINATION ${MUGENGINE_INSTALL_INCLUDE_DIR})