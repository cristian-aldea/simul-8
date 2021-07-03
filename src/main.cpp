#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "common/utils.h"
#include "common/constants.h"

#include "models/Cube.h"

using std::cout;
using std::cerr;
using std::endl;

using glm::vec3;
using glm::mat4;

using simul8::loadShaders;
using simul8::init;
using simul8::Vertex;
using simul8::setUniform;

GLFWwindow *window;

vec3 up = vec3(0, 1, 0);

int main() {
    window = init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Ensure we can capture the escape key being pressed below.
    // TODO: implement proper input handling with listener
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint shader = loadShaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    glUseProgram(shader);

    Cube::loadCube();

    // TODO move to camera
    mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    setUniform(shader, projectionMatrix, UNIFORM_PROJECTION_MATRIX_NAME);

    mat4 viewMatrix = glm::lookAt(vec3(1, 1, 2), vec3(0, 0, 0), up);
    setUniform(shader, viewMatrix, UNIFORM_VIEW_MATRIX_NAME);

    Cube cube(shader);

    glClearColor(0, 0, 0.2f, 0);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.draw(MAT4_I);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}
