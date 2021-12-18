#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal;

out vec3 fragmentPos;
out vec3 fragmentNormal;
out vec2 fragmentUV;
out vec4 fragmentPosLightSpace;

uniform mat4 projectionMatrix = mat4(1);
uniform mat4 viewMatrix = mat4(1);
uniform mat4 modelMatrix = mat4(1);
uniform mat4 lightSpaceMatrix;

void main() {
    fragmentPos = vec3(modelMatrix * vec4(vertexPosition, 1));
    fragmentNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    fragmentUV = vertexUV;
    fragmentPosLightSpace = lightSpaceMatrix * vec4(fragmentPos, 1.0);

    gl_Position = projectionMatrix * viewMatrix * vec4(fragmentPos, 1);
}
