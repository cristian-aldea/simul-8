#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

using glm::mat4;
using glm::vec3;

class Cube : public RenderedModel {
public:
    explicit Cube(GLuint shader);
    static void loadCube();

private:
    static GLuint vao;
    static GLuint vbo;
    static const GLsizei cubeNumVertices = 36;

    void drawVertices() const override;
    GLuint getVAO() const override;
    GLuint getVBO() const override;
    GLsizei getNumVertices() const override;

};
