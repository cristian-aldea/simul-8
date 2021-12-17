#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Model.h"

class RenderedModel : public Model {
public:
    GLuint shader;
    GLuint texture;
    explicit RenderedModel(GLuint shader, GLuint texture);

    void draw(mat4 parent) override;

    virtual void drawVertices() const = 0;
    virtual GLuint getVAO() const = 0;
    virtual GLuint getVBO() const = 0;
};
