#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Cylinder : public RenderedModel {
public:
    explicit Cylinder(GLuint shader);
    void loadModel();

private:
    GLsizei numVertices = 0;

    void drawVertices() const override;
    GLsizei getNumVertices() const override;

};

