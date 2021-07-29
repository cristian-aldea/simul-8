#version 330 core

in vec3 fragmentColor;
in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec3 cameraPos;

out vec3 color;

vec3 lightColor = vec3(1);
vec3 lightPos = vec3(2, 6, 4);

// These values should be between 0 and 1
float ambientStrength = 0.2;
float diffuseStrength = 0.8;
float specularStrength = 0.5;

int specPow = 64;

vec3 getAmbient(){
    return ambientStrength * lightColor;
}

vec3 getDiffuse(vec3 normal, vec3 lightDir){
    float diff = clamp(dot(normal, -lightDir), 0, 1);

    return diffuseStrength * diff * lightColor;
}

vec3 getSpecular(vec3 normal, vec3 lightDir){
    vec3 reflect = reflect(lightDir, normal);
    vec3 viewDir = normalize(fragmentPos - cameraPos);
    float spec = pow(clamp(dot(viewDir, -reflect), 0, 1) ,specPow);

    return specularStrength * spec * lightColor;
}


void main(){
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDir = normalize(fragmentPos - lightPos);

    vec3 ambient = getAmbient();
    vec3 diffuse = getDiffuse(normal, lightDir);
    vec3 specular = getSpecular(normal, lightDir);
    float distance = distance(fragmentPos, lightPos);

    vec3 result = (ambient + diffuse + specular)  * fragmentColor;

    color = result;
}
