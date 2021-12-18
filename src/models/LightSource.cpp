#include "LightSource.h"

#include "../common/globals.h"

using s8::defaultTexture;
using s8::setUniform;
using s8::UNIFORM_LIGHT_POSITION_NAME;


LightSource::LightSource(GLuint shader) : LightSource(shader, defaultTexture) {}

LightSource::LightSource(GLuint shader, GLuint texture) {
    sphere = new Sphere(shader, texture);
    this->shader = shader;
}

void LightSource::draw(mat4 parent) {
    sphere->draw(parent);
}

void LightSource::setPosition(vec3 position) {
    sphere->position = position;

    setUniform(shader, position, UNIFORM_LIGHT_POSITION_NAME);
}

vec3 LightSource::getPosition() {
    return sphere->position;
}
