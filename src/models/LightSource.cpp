#include "LightSource.h"

#include "../common/globals.h"

using s8::defaultTexture;
using s8::setUniform;
using s8::UNIFORM_LIGHT_POSITION_NAME;


LightSource::LightSource() : LightSource(defaultTexture) {}

LightSource::LightSource(GLuint texture) {
    sphere = new Sphere(texture);
    sphere->scale = vec3(0.5);
}

void LightSource::draw(mat4 parent, GLuint shader) const {
    sphere->draw(parent, shader);
}

void LightSource::setPosition(vec3 position, GLuint shader) const {
    sphere->position = position;

    setUniform(shader, position, UNIFORM_LIGHT_POSITION_NAME);
}

vec3 LightSource::getPosition() const {
    return sphere->position;
}
