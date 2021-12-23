#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common/utils.h"
#include "common/globals.h"
#include "models/Cube.h"
#include "models/Cylinder.h"
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
using s8::SHADOW_WIDTH;
using s8::SHADOW_HEIGHT;

void render(GLuint shader);
void update(double dt);
void configureLightMatrices();
void renderDebugQuad();
void setupShadowMapping();
void renderDepthMap();


unsigned int quadVAO = 0;
unsigned int quadVBO;
unsigned int depthMapFBO;
unsigned int depthMap;

GLuint blueTexture;
GLuint brickTexture;
GLuint floorTexture;
GLuint greenTexture;
GLuint redTexture;
GLuint whiteTexture;

GLuint mainShader;
GLuint depthShader;
GLuint debugShader;

GLFWwindow *window;
Camera *camera;
Cube *stageFloor;
Cube *brick;
Cube *brick2;
Cylinder *cylinder;
LightSource *lightSource;


int main() {
    // init objects
    window = init();
    s8::window = window;

    // init settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    mainShader = loadShaders("assets/mainShader/vertex.shader", "assets/mainShader/fragment.shader");
    depthShader = loadShaders("assets/depthMapShader/vertex.shader", "assets/depthMapShader/fragment.shader");
    debugShader = loadShaders("assets/debugShader/vertex.shader", "assets/debugShader/fragment.shader");

    blueTexture = s8::loadTexture("assets/textures/blue.jpg");
    brickTexture = s8::loadTexture("assets/textures/brick.jpg");
    defaultTexture = s8::loadTexture("assets/textures/default.jpg");
    floorTexture = s8::loadTexture("assets/textures/floor-tile.jpg");
    greenTexture = s8::loadTexture("assets/textures/green.jpg");
    redTexture = s8::loadTexture("assets/textures/red.jpg");
    whiteTexture = s8::loadTexture("assets/textures/white.jpg");


    stageFloor = new Cube(floorTexture, vec3(50, 1, 50));
    stageFloor->position = vec3(0, -0.5, 0);

    brick = new Cube(brickTexture);
    brick->position = vec3(2, 1, 2);

    brick2 = new Cube(brickTexture);
    brick2->position = vec3(-1, 0.5, -1);

    cylinder = new Cylinder();
    cylinder->scale = vec3(0.1, 0.1, 2);

    lightSource = new LightSource(whiteTexture);
    lightSource->setPosition(vec3(-2, 3, 1), mainShader);

    camera = new Camera(mainShader, vec3(0, 1, 2));

    s8::camera = camera;

    // depth map stuff
    setupShadowMapping();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);


    double lastFrameTime = glfwGetTime();
    do {
        // setup
        double currTime = glfwGetTime();
        double dt = glfwGetTime() - lastFrameTime;
        lastFrameTime = currTime;

        // render depth map
        renderDepthMap();

        // reset to normal stuff
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, s8::WINDOW_WIDTH, s8::WINDOW_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        renderDebugQuad();
        render(mainShader);

        // end of rendering
        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();

        update(dt);

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}

void render(GLuint shader) {
    glUseProgram(shader);

    stageFloor->draw(MAT4_I, shader);
    brick->draw(MAT4_I, shader);
    brick2->draw(MAT4_I, shader);

    // render axes
    cylinder->position = vec3(1, 0, 0);
    cylinder->rotation = Rotation(90, vec3(0, 1, 0));
    cylinder->texture = redTexture;
    cylinder->draw(MAT4_I, shader);
    cylinder->position = vec3(0, 1, 0);
    cylinder->rotation = Rotation(90, vec3(1, 0, 0));
    cylinder->texture = greenTexture;
    cylinder->draw(MAT4_I, shader);
    cylinder->position = vec3(0, 0, 1);
    cylinder->rotation = Rotation(0, vec3(0, 1, 0));
    cylinder->texture = blueTexture;
    cylinder->draw(MAT4_I, shader);

    lightSource->draw(MAT4_I, shader);
}

void update(double dt) {
    camera->update(window, dt);
}

void setupShadowMapping() {
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
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

    // setup sampler2D uniforms
    glUseProgram(debugShader);
    setUniform(debugShader, 0, "depthMap");
    glUseProgram(mainShader);
    setUniform(mainShader, 0, "ourTexture");
    setUniform(mainShader, 1, "shadowMap");
}

void renderDepthMap() {
    float near_plane = 1.0f, far_plane = 20.5f;
    mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    mat4 lightView = glm::lookAt(lightSource->getPosition(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    mat4 lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    glUseProgram(mainShader);
    setUniform(mainShader, lightSpaceMatrix, "lightSpaceMatrix");
    glUseProgram(depthShader);
    setUniform(depthShader, lightSpaceMatrix, "lightSpaceMatrix");
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    render(depthShader);
}


void renderDebugQuad() {
    glUseProgram(debugShader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions  (1,2,3)          // texture Coords (4,5)
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