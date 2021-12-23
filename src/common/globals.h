#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/Camera.h"

using glm::mat4;

namespace s8 {
    extern GLFWwindow *window;
    extern Camera *camera;
    extern GLuint defaultTexture;

    extern const mat4 MAT4_I;

    extern const char *const UNIFORM_MODEL_MATRIX_NAME;
    extern const char *const UNIFORM_VIEW_MATRIX_NAME;
    extern const char *const UNIFORM_PROJECTION_MATRIX_NAME;
    extern const char *const UNIFORM_CAMERA_POSITION_NAME;
    extern const char *const UNIFORM_LIGHT_POSITION_NAME;
    extern const char *const UNIFORM_LIGHT_SPACE_MATRIX_NAME;

    extern const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;
    extern const float WINDOW_RATIO;
    extern const int SHADOW_WIDTH;
    extern const int SHADOW_HEIGHT;
};
