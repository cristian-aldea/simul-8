#pragma once

#include <GL/glew.h> // Always include glew first
#include <GLFW/glfw3.h>

namespace simul8 {
    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);
    GLFWwindow *init();

}
