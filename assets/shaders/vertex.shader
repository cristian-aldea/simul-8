#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 modelMatrix = mat4(1);
uniform mat4 viewMatrix = mat4(1);
uniform mat4 projectionMatrix = mat4(1);

out vec3 fragmentColor;

void main() {
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    gl_Position = mvp * vec4(vertexPosition, 1);

    // Pass to fragment shader
    fragmentColor = vertexColor;
}
