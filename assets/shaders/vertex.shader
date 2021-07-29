#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexUV;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix = mat4(1);
uniform mat4 viewMatrix = mat4(1);
uniform mat4 projectionMatrix = mat4(1);
uniform vec3 cameraPosition = vec3(1);

out vec3 fragmentColor;
out vec3 fragmentPos;
out vec3 fragmentNormal;
out vec3 cameraPos;

void main() {
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    gl_Position = mvp * vec4(vertexPosition, 1);
    fragmentPos = vec3(modelMatrix * vec4(vertexPosition, 1));

    fragmentNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;

    // Pass to fragment shader
    fragmentColor = vertexColor;

    cameraPos = cameraPosition;
}
