cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(PROJECT_NAME simul-8)

project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw glm glew)

set(HEADER_FILES

)

set(SRC_FILES
    src/main.cpp
)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
