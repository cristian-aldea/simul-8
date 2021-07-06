#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../common/constants.h"

Model::Model() :
        name{"NO_NAME"},
        position{vec3(0)},
        scale{vec3(1)},
        rotation{Rotation()} {}

Model::Model(vec3 position) :
        name{"NO_NAME"},
        position{position},
        scale{vec3(1)},
        rotation{Rotation()} {}

mat4 Model::getMVPMatrix() const {
    return glm::translate(MAT4_I, position)
           * glm::rotate(MAT4_I, glm::radians(0.0f), vec3(1, 0, 0))
           * glm::scale(MAT4_I, vec3(1));
}


