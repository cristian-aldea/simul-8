#pragma once


#include "Sphere.h"

class LightSource {
public:
    explicit LightSource();
    LightSource(GLuint texture);
    void draw(mat4 parent, GLuint shader) const;

    void setPosition(vec3 position, GLuint shader) const;
    vec3 getPosition() const;

    Sphere *sphere;
};

