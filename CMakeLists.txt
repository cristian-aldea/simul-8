cmake_minimum_required(VERSION 3.13)

project(simul8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
set(ALL_LIBS ${OPENGL_LIBRARY} glfw glm glew_s)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# make sure OpenGL is available
find_package(OpenGL REQUIRED)

# glfw
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(external/glfw EXCLUDE_FROM_ALL)

# glm
set(BUILD_STATIC_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

# glew
set(BUILD_UTILS OFF)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
add_subdirectory(external/glew/build/cmake external/glew EXCLUDE_FROM_ALL)

set(HEADER_FILES
        src/common/utils.h
        )

set(SRC_FILES
        src/main.cpp
        src/common/utils.cpp
        )

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE external/glew/include
        )

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})


# install files to install location
install(TARGETS ${PROJECT_NAME}
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

# Copy assets to build directory
configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/fragment.shader ${CMAKE_BINARY_DIR}/assets/shaders/fragment.shader COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/vertex.shader ${CMAKE_BINARY_DIR}/assets/shaders/vertex.shader COPYONLY)

# Copy assets to install directory if Release
if (${CMAKE_BUILD_TYPE} MATCHES Release)
    configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/fragment.shader ${CMAKE_INSTALL_PREFIX}/assets/shaders/fragment.shader COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/assets/shaders/vertex.shader ${CMAKE_INSTALL_PREFIX}/assets/shaders/vertex.shader COPYONLY)
endif ()
