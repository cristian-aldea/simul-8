#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "./RenderedModel.h"

using glm::vec3;
using std::vector;
using glm::mat4;

class Sphere : public RenderedModel {
public:
    explicit Sphere(GLuint shader);
    explicit Sphere(GLuint shader, GLuint texture);


private:
    static GLsizei numVertices;
    static GLsizei numIndices;
    static GLuint vao;
    static GLuint vbo;
    static GLuint ibo;
    static bool loaded;

    void drawVertices() const override;
    static void loadModel();

    GLuint getVAO() const override;
    GLuint getVBO() const override;
};