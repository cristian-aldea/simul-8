#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Line : public RenderedModel {
public:
    explicit Line();
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
