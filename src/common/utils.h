#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec2;
using glm::mat4;

namespace s8 {
    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);
    GLFWwindow *init();

    struct Vertex {
        vec3 position;
        vec3 color;
        vec2 uv;
        vec3 normal;

        Vertex(vec3 position, vec3 color) :
                position{position},
                color{color},
                uv{vec2(0)},
                normal{vec3(0, 1, 0)} {}

        Vertex(vec3 position, vec3 color, vec2 uv, vec3 normal) :
                position{position},
                color{color},
                uv{uv},
                normal{normal} {}
    };

    struct Rotation {
        float angle;
        vec3 axis;

        Rotation() :
                angle{0},
                axis{vec3(1)} {}

        Rotation(float angle, vec3 axis) :
                angle{angle},
                axis{axis} {}
    };

    void setUniform(GLuint shaderProgram, mat4 matrix, const char *name);
    void setUniform(GLuint shaderProgram, vec3 vector, const char *name);
    void setUniform(GLuint shaderProgram, vec2 vector, const char *name);
    void setUniform(GLuint shaderProgram, bool boolean, const char *name);

    float rng(float min, float max);
    float rng();

}
