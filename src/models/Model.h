#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../common/utils.h"

using std::string;
using std::vector;

using glm::vec3;
using glm::mat4;

using s8::Rotation;

class Model {
public:
    string name;
    vec3 position;
    vec3 scale;
    Rotation rotation;
    vector<Model *> children;

    Model();

    virtual void draw(mat4 parent, GLuint shader);
    void addChild(Model *child);

    mat4 getMVPMatrix() const;
};
