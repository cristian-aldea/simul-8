#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common/utils.h"

#include "models/Cube.h"
#include "models/Cylinder.h"
#include "models/Line.h"
#include "models/Camera.h"
#include "common/globals.h"

using std::cout;
using std::cerr;
using std::endl;

using glm::vec3;
using glm::mat4;

using s8::loadShaders;
using s8::init;
using s8::Vertex;
using s8::setUniform;
using s8::MAT4_I;

int main() {
    GLFWwindow *window = init();
    s8::window = window;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint shader = loadShaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    glUseProgram(shader);

    Cube::loadCube();
    Cylinder::loadModel();
    Line::loadModel();

    Cube floor(shader);
    floor.position = vec3(0, -0.1, 0);
    floor.scale = vec3(50, 0.01, 50);

    Cube cube(shader);
    cube.position = vec3(0, 1, 0);
    cube.rotation = Rotation(180, vec3(0, 0, 1));

    Cylinder cylinder(shader);
    cylinder.position = vec3(0, 3, 0);

    Line line(shader);

    Camera camera(shader, vec3(-2, 1, 0));

    s8::camera = &camera;

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    double lastFrameTime = glfwGetTime();
    do {
        double currTime = glfwGetTime();
        double dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = currTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        floor.draw(MAT4_I);
        cube.draw(MAT4_I);
        cylinder.draw(MAT4_I);
        line.draw(MAT4_I);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        camera.update(window, dt);

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}
