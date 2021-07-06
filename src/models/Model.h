#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../common/utils.h"

using std::string;

using glm::vec3;
using glm::mat4;

using simul8::Rotation;

class Model {
public:
    string name;
    vec3 position;
    vec3 scale;
    Rotation rotation;

    Model();
    explicit Model(vec3 position);
    virtual void draw(mat4 parent) = 0;

    mat4 getMVPMatrix() const;
};
