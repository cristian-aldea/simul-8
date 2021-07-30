#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common/utils.h"
#include "common/constants.h"

#include "models/Cube.h"
#include "models/Cylinder.h"
#include "models/Line.h"
#include "models/Camera.h"
#include "controller/Controller.h"

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

int main() {
    window = init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Ensure we can capture the escape key being pressed below.
    // TODO: implement proper input handling with listener
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint shader = loadShaders("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    glUseProgram(shader);

    Cube::loadCube();
    Cylinder::loadModel();
    Line::loadModel();

    Cube cube(shader);
    cube.rotation = Rotation(180, vec3(0, 0, 1));

    Cylinder cylinder(shader);
    cylinder.position = vec3(0, 2, 0);

    Line line(shader);

    Camera camera(shader, vec3(-2, 0, 0));
//    Controller controller(window, &camera);


    glClearColor(0.5f, 0.5f, 0.5f, 1);

    double lastFrameTime = glfwGetTime();
    do {
        double currTime = glfwGetTime();
        double dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = currTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
