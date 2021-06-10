cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(PROJECT_NAME simul8)

project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw glm glew)

set(HEADER_FILES
    src/common/utils.h
)

set(SRC_FILES
    src/main.cpp
    src/common/utils.cpp
)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

# Copy shaders to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
