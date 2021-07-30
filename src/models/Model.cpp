#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../common/constants.h"

Model::Model() :
        name{"NO_NAME"},
        position{vec3(0)},
        scale{vec3(1)},
        rotation{Rotation()} {}

mat4 Model::getMVPMatrix() const {
    return glm::translate(MAT4_I, position)
           * glm::rotate(MAT4_I, glm::radians(rotation.angle), rotation.axis)
           * glm::scale(MAT4_I, vec3(1));
}

void Model::draw(mat4 parent) {
    for (const auto &child : children) {
        child->draw(this->getMVPMatrix());
    }
}

void Model::addChild(Model *child) {
    this->children.push_back(child);
}


