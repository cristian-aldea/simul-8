#include "globals.h"

using glm::mat4;

namespace s8 {
    const mat4 MAT4_I = mat4(1);

    GLFWwindow *window = nullptr;
    Camera *camera = nullptr;

    const char *const UNIFORM_MODEL_MATRIX_NAME = "modelMatrix";
    const char *const UNIFORM_VIEW_MATRIX_NAME = "viewMatrix";
    const char *const UNIFORM_PROJECTION_MATRIX_NAME = "projectionMatrix";
    const char *const UNIFORM_CAMERA_POSITION_NAME = "cameraPosition";

    const int WINDOW_WIDTH = 1600;
    const int WINDOW_HEIGHT = 900;
    const float WINDOW_RATIO = (float) WINDOW_WIDTH / WINDOW_HEIGHT;
}
