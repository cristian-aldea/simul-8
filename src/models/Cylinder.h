#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Model.h"

class Cylinder : public Model {
public:
    Cylinder(GLuint shader, vec3 position);
    explicit Cylinder(GLuint shader);

    void draw(mat4 parent) override;

    GLuint shader;

    static void loadModel();

private:
    static int numVertices;
    static unsigned int cylinderVAO;
    static unsigned int cylinderVBO;

};

