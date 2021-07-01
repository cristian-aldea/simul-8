cmake_minimum_required(VERSION 3.13)

project(simul8)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw glm glew_s)

set(HEADER_FILES
        src/common/utils.h
        )

set(SRC_FILES
        src/main.cpp
        src/common/utils.cpp
        )
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/glew/build/cmake external/glew)


set(BUILD_UTILS OFF)
set(BUILD_SHARED_LIBS OFF)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE external/glew/include
        )

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

# Copy assets to the build directory
configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/fragment.shader ${CMAKE_BINARY_DIR}/assets/shaders/fragment.shader COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/vertex.shader ${CMAKE_BINARY_DIR}/assets/shaders/vertex.shader COPYONLY)
