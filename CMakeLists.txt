cmake_minimum_required(VERSION 3.13)

project(simul8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
set(ALL_LIBS ${OPENGL_LIBRARY} glfw glm glad)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# make sure OpenGL is available
find_package(OpenGL REQUIRED)

# glad
add_subdirectory(external/glad)

# glfw
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC OFF)
add_subdirectory(external/glfw EXCLUDE_FROM_ALL)

# glm
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

set(HEADER_FILES
        src/common/globals.h
        src/common/utils.h

        src/external/stb_image.h

        src/models/Camera.h
        src/models/Cube.h
        src/models/Cylinder.h
        src/models/LightSource.h
        src/models/Line.h
        src/models/Model.h
        src/models/RenderedModel.h
        src/models/Sphere.h
        )

set(SRC_FILES
        src/common/globals.cpp
        src/common/utils.cpp

        src/external/stb_image.cpp

        src/models/Camera.cpp
        src/models/Cube.cpp
        src/models/Cylinder.cpp
        src/models/Line.cpp
        src/models/LightSource.cpp
        src/models/Model.cpp
        src/models/RenderedModel.cpp
        src/models/Sphere.cpp

        src/main.cpp

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
set(ASSETS
        assets/debugShader/fragment.shader
        assets/debugShader/vertex.shader
        assets/depthMapShader/fragment.shader
        assets/depthMapShader/vertex.shader
        assets/mainShader/fragment.shader
        assets/mainShader/vertex.shader
        assets/textures/blue.jpg
        assets/textures/brick.jpg
        assets/textures/default.jpg
        assets/textures/floor-tile.jpg
        assets/textures/green.jpg
        assets/textures/red.jpg
        assets/textures/white.jpg
        )

foreach (ASSET ${ASSETS})
    configure_file(${CMAKE_SOURCE_DIR}/${ASSET} ${CMAKE_BINARY_DIR}/${ASSET} COPYONLY)
endforeach ()

# Copy assets to install directory if Release
if (${CMAKE_BUILD_TYPE} MATCHES Release)
    foreach (ASSET ${ASSETS})
        configure_file(${CMAKE_SOURCE_DIR}/${ASSET} ${CMAKE_INSTALL_PREFIX}/${ASSET} COPYONLY)
    endforeach ()
endif ()
