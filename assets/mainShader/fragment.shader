#version 330 core

in vec3 fragmentPos;
in vec3 fragmentColor;
in vec3 fragmentNormal;
in vec2 fragmentUV;
in vec4 fragmentPosLightSpace;

uniform sampler2D ourTexture;
uniform sampler2D shadowMap;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec4 fragColor;

vec4 lightColor = vec4(1, 1, 1, 0);

// These values should be between 0 and 1
float ambientStrength = 0.2;
float diffuseStrength = 0.8;
float specularStrength = 0.5;

int specPow = 64;

vec4 getAmbient(){
    return ambientStrength * lightColor;
}

vec4 getDiffuse(vec3 normal, float dotLightNormal){
    float result = dotLightNormal * sign(dotLightNormal);
    float diff = clamp(result, 0, 1);

    return diffuseStrength * diff * lightColor;
}

vec4 getSpecular(vec3 normal, vec3 lightDir){
    vec3 reflect = reflect(lightDir, normal);
    vec3 viewDir = normalize(fragmentPos - cameraPosition);
    float spec = pow(clamp(dot(viewDir, -reflect), 0, 1), specPow);

    return specularStrength * spec * lightColor;
}

float shadowCalc(float dotLightNormal)
{
    // perform perspective divide
    vec3 pos = fragmentPosLightSpace.xyz / fragmentPosLightSpace.w;
    // transform to [0,1] range
    pos = pos * 0.5 + 0.5;
    if (pos.z > 1.0){
        pos.z = 1.0;
    }
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, pos.xy).r;
    // check whether current frag pos is in shadow
    float bias = min(0.05 * dotLightNormal, 0.005);

    return pos.z > closestDepth + bias ? 0.0 : 1.0;
}

void main(){
    vec4 color = texture(ourTexture, fragmentUV);
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDir = normalize(fragmentPos - lightPosition);
    float dotLightNormal = dot(normal, -lightDir);

    vec4 ambient = getAmbient();
    vec4 diffuse = getDiffuse(normal, dotLightNormal);
    vec4 specular = getSpecular(normal, lightDir);

    float shadow = shadowCalc(dotLightNormal);

    fragColor = (ambient + shadow * (diffuse + specular))  * color;
    //    fragColor = (ambient + diffuse + specular)  * color;
}
