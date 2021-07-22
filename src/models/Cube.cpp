#include "Cube.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "../common/constants.h"

using glm::vec3;

using simul8::Vertex;
using simul8::setUniform;
using simul8::rng;

unsigned int Cube::cubeVAO = 0;
unsigned int Cube::cubeVBO = 0;

Cube::Cube(GLuint shaderProgram) :
        shaderProgram{shaderProgram},
        position{vec3(0)} {}

void Cube::draw(mat4 parent) {
    // Draw the cube
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    mat4 modelMatrix = glm::translate(MAT4_I, position)
                       * glm::rotate(MAT4_I, glm::radians(rotation.angle), rotation.axis)
                       * glm::scale(MAT4_I, scale);

    setUniform(shaderProgram, parent * modelMatrix, UNIFORM_MODEL_MATRIX_NAME);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

}

void Cube::loadCube() {
    Vertex vertices[] = {
            // Top
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 0
            Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 2
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 3
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 0
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 3
            Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 1, 0)), // 1

            // Front
            Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 2
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 6
            Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 7
            Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 2
            Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 7
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(-1, 0, 0)), // 3

            // Right
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 3
            Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 7
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 5
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 3
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 5
            Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(0, 0, 1)), // 1

            // Left
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 0
            Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 4
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 6
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 0
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 6
            Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(0, 0, -1)), // 2

            // Back
            Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 1
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 5
            Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 4
            Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 1
            Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 4
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0), vec2(0), vec3(1, 0, 0)), // 0

            // Bottom
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 6
            Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 4
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 5
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 6
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 5
            Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0), vec2(0), vec3(0, -1, 0)), // 7
    };

    for (auto &vertex : vertices) {
        vertex.color = vec3(rng(), rng(), rng());
    }

    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3) + sizeof(vec2)));
    glEnableVertexAttribArray(3);
}




