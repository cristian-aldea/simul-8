#version 330 core

in vec3 fragmentPos;
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec2 fragmentUV;
in vec3 cameraPos;

uniform sampler2D ourTexture;

out vec4 color;

vec4 lightColor = vec4(1, 1, 1, 0);
vec3 lightPos = vec3(2, 6, 4);

// These values should be between 0 and 1
float ambientStrength = 0.2;
float diffuseStrength = 0.8;
float specularStrength = 0.5;

int specPow = 64;

vec4 getAmbient(){
    return ambientStrength * lightColor;
}

vec4 getDiffuse(vec3 normal, vec3 lightDir){
    float diff = clamp(dot(normal, -lightDir), 0, 1);

    return diffuseStrength * diff * lightColor;
}

vec4 getSpecular(vec3 normal, vec3 lightDir){
    vec3 reflect = reflect(lightDir, normal);
    vec3 viewDir = normalize(fragmentPos - cameraPos);
    float spec = pow(clamp(dot(viewDir, -reflect), 0, 1), specPow);

    return specularStrength * spec * lightColor;
}


void main(){
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDir = normalize(fragmentPos - lightPos);

    vec4 ambient = getAmbient();
    vec4 diffuse = getDiffuse(normal, lightDir);
    vec4 specular = getSpecular(normal, lightDir);
    float distance = distance(fragmentPos, lightPos);

    vec4 baseColor = texture(ourTexture, fragmentUV);

    vec4 result = (ambient + diffuse + specular)  * baseColor;

    color = result;
}
