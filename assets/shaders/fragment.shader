#version 330 core

in vec3 fragmentColor;
in vec3 fragmentPos;
in vec3 fragmentNormal;

out vec3 color;

vec3 lightColor = vec3(1);
vec3 lightPos = vec3(2, 6, 4);

float ambientStrength = 0.2;


void main(){
    vec3 ambient = ambientStrength * lightColor;

    vec3 normal = normalize(fragmentNormal);
    vec3 lightDir = normalize(lightPos - fragmentPos);
    float diff = clamp(dot(normal, lightDir), 0, 1);

    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * fragmentColor;

    color = result;
}
