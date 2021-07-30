#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Line: public RenderedModel {
public:
    explicit Line(GLuint shader);
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
