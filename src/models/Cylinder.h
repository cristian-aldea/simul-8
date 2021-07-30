#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Cylinder : public RenderedModel {
public:
    explicit Cylinder(GLuint shader);
    static void loadModel();

private:
    static GLuint vao;
    static GLuint vbo;
    static GLsizei numVertices;

    void drawVertices() const override;
    GLuint getVAO() const override;
    GLuint getVBO() const override;
    GLsizei getNumVertices() const override;

};

