#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../models/Camera.h"

class Controller {
public:
    Controller(GLFWwindow *window, Camera *camera);
private:
    void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    Camera *camera;
};
