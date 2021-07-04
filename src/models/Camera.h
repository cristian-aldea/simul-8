#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using glm::vec3;

class Camera {
public:
    Camera(GLuint shader, vec3 position);
    void update(GLFWwindow *window, float dt);
    vec3 position;
    vec3 look;
    vec3 up;
private:
    void updateMatrices() const;
    double horizontalAngle;
    double verticalAngle;
    float fov;
    GLuint shader;

    double cameraViewSpeed = 15;
    float cameraSpeed = 5;

    double mouseX, mouseY;
};
