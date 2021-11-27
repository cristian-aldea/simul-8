#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "RenderedModel.h"

class Line : public RenderedModel {
public:
    explicit Line(GLuint shader);
private:
    GLsizei numVertices = 0;

    void loadModel();

    void drawVertices() const override;
    GLsizei getNumVertices() const override;


};
