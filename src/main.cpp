#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common/utils.h"
#include "common/globals.h"
#include "models/Cube.h"
#include "models/Cylinder.h"
#include "models/Line.h"
#include "models/Camera.h"
#include "models/LightSource.h"

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
using s8::defaultTexture;
using s8::Rotation;

void drawAxes(Cylinder *cylinder, GLuint redTexture, GLuint greenTexture, GLuint blueTexture);

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

    GLuint blueTexture = s8::loadTexture("assets/textures/blue.jpg");
    GLuint brickTexture = s8::loadTexture("assets/textures/brick.jpg");
    defaultTexture = s8::loadTexture("assets/textures/default.jpg");
    GLuint floorTexture = s8::loadTexture("assets/textures/floor-tile.jpg");
    GLuint greenTexture = s8::loadTexture("assets/textures/green.jpg");
    GLuint redTexture = s8::loadTexture("assets/textures/red.jpg");
    GLuint whiteTexture = s8::loadTexture("assets/textures/white.jpg");

    Cube floor(shader, floorTexture, vec3(50, 1, 50), vec3(1));
    floor.position = vec3(0, -0.6, 0);

    Cube brick(shader, brickTexture);
    brick.position = vec3(2, 1, 2);

    Cylinder cylinder(shader);
    cylinder.scale = vec3(0.1, 0.1, 2);

    LightSource lightSource(shader, whiteTexture);
    lightSource.setPosition(vec3(0, 8, 0));

    Camera camera(shader, vec3(0, 1, 2));

    s8::camera = &camera;

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    double lastFrameTime = glfwGetTime();
    do {
        // PRE DRAW SETUP
        double currTime = glfwGetTime();
        double dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = currTime;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // DRAW START
        floor.draw(MAT4_I);
        brick.draw(MAT4_I);
        drawAxes(&cylinder, redTexture, greenTexture, blueTexture);
        lightSource.draw(MAT4_I);

        // DRAW DONE
        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();

        camera.update(window, dt);

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}

void drawAxes(Cylinder *cylinder, GLuint redTexture, GLuint greenTexture, GLuint blueTexture) {
    // render axes
    cylinder->position = vec3(1, 0, 0);
    cylinder->rotation = Rotation(90, vec3(0, 1, 0));
    cylinder->texture = redTexture;
    cylinder->draw(MAT4_I);
    cylinder->position = vec3(0, 1, 0);
    cylinder->rotation = Rotation(90, vec3(1, 0, 0));
    cylinder->texture = greenTexture;
    cylinder->draw(MAT4_I);
    cylinder->position = vec3(0, 0, 1);
    cylinder->rotation = Rotation(0, vec3(0, 1, 0));
    cylinder->texture = blueTexture;
    cylinder->draw(MAT4_I);
}
