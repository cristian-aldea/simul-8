#include "Controller.h"

#include <iostream>

Controller::Controller(GLFWwindow *window, Camera *camera) :
        camera{camera} {
    // TODO
//    glfwSetKeyCallback(window, keyCallBack);
}

void Controller::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << ", scancode: " << scancode << ", action: " << action << ", mods: " << mods << std::endl;

    vec3 cameraSideVector = glm::normalize(glm::cross(camera->look, vec3(0.0f, 1.0f, 0.0f)));
    if (key == GLFW_KEY_A && action == GLFW_PRESS || action == GLFW_REPEAT) {

    }
}
