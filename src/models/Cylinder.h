#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Cylinder : public RenderedModel {
public:
    explicit Cylinder();

private:
    static GLsizei numVertices;
    static GLuint vao;
    static GLuint vbo;
    static bool loaded;

    void drawVertices() const override;
    static void loadModel();

    GLuint getVAO() const override;
    GLuint getVBO() const override;
};

