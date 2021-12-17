#pragma once


#include "Sphere.h"

class LightSource {
public:
    explicit LightSource(GLuint shader);
    LightSource(GLuint shader, GLuint texture);
    void draw(mat4 parent);

    void setPosition(vec3 position);
private:
    Sphere *sphere;
    GLuint shader;
};

