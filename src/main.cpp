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

void render(GLuint shader);
void update(double dt);
void configureLightMatrices();

// =============================================================================================================
// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;

void renderQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
// =============================================================================================================



GLuint blueTexture;
GLuint brickTexture;
GLuint floorTexture;
GLuint greenTexture;
GLuint redTexture;
GLuint whiteTexture;

GLFWwindow *window;

Cube *stageFloor;
Cube *brick;
Cylinder *cylinder;
LightSource *lightSource;
Camera *camera;


int main() {
    window = init();
    s8::window = window;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint shader = loadShaders("assets/shader/vertex.shader", "assets/shader/fragment.shader");
    GLuint depthShader = loadShaders("assets/depthMapShader/vertex.shader", "assets/depthMapShader/fragment.shader");
    GLuint debugShader = loadShaders("assets/debugDepthShader/vertex.shader",
                                     "assets/debugDepthShader/fragment.shader");

    blueTexture = s8::loadTexture("assets/textures/blue.jpg");
    brickTexture = s8::loadTexture("assets/textures/brick.jpg");
    defaultTexture = s8::loadTexture("assets/textures/default.jpg");
    floorTexture = s8::loadTexture("assets/textures/floor-tile.jpg");
    greenTexture = s8::loadTexture("assets/textures/green.jpg");
    redTexture = s8::loadTexture("assets/textures/red.jpg");
    whiteTexture = s8::loadTexture("assets/textures/white.jpg");


    stageFloor = new Cube(shader, floorTexture, vec3(50, 1, 50), vec3(1));
    stageFloor->position = vec3(0, -0.6, 0);

    brick = new Cube(shader, brickTexture);
    brick->position = vec3(1, 1, 1);

    cylinder = new Cylinder(shader);
    cylinder->scale = vec3(0.1, 0.1, 2);

    lightSource = new LightSource(shader, whiteTexture);
    lightSource->setPosition(vec3(-4, 2, 3));

    camera = new Camera(shader, vec3(0, 1, 2));

    s8::camera = camera;

    // depth map stuff
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(debugShader);
    setUniform(debugShader, 0, "depthMap");

    glUseProgram(shader);
    setUniform(shader, 0, "ourTexture");
    setUniform(shader, 1, "shadowMap");


    double lastFrameTime = glfwGetTime();
    do {
        // setup
        double currTime = glfwGetTime();
        double dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = currTime;
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 20.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightSource->getPosition(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        glUseProgram(depthShader);
        setUniform(depthShader, lightSpaceMatrix, "lightSpaceMatrix");

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        render(depthShader);

        // reset to normal stuff
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, s8::WINDOW_WIDTH, s8::WINDOW_HEIGHT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render Depth map to quad for visual debugging
        // ---------------------------------------------
//        glUseProgram(debugShader);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, depthMap);
//        renderQuad();

        // render normally
        glUseProgram(shader);
        setUniform(shader, lightSpaceMatrix, "lightSpaceMatrix");
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        render(shader);

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();

        update(dt);

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}


void render(GLuint shader) {
    glUseProgram(shader);
    stageFloor->shader = shader;
    brick->shader = shader;
    cylinder->shader = shader;
    lightSource->sphere->shader = shader;


    stageFloor->draw(MAT4_I);
    brick->draw(MAT4_I);


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

    lightSource->draw(MAT4_I);
}

void update(double dt) {
    camera->update(window, dt);

//    lightSource->setPosition(lightSource->getPosition() + vec3(0, 1 * dt, 0));
}

