#include "Cube.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "../common/utils.h"
#include "../common/constants.h"

using glm::vec3;

using simul8::Vertex;
using simul8::setUniform;

unsigned int Cube::cubeVAO = 0;
unsigned int Cube::cubeVBO = 0;
unsigned int Cube::cubeIBO = 0;

Cube::Cube(GLuint shaderProgram) :
        shaderProgram{shaderProgram},
        position{vec3(0)} {}

void Cube::draw(mat4 parent) {
    // Draw the cube
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    mat4 modelMatrix = glm::translate(MAT4_I, position)
                       * glm::rotate(MAT4_I, glm::radians(0.0f), vec3(1, 0, 0))
                       * glm::scale(MAT4_I, vec3(1));

    setUniform(shaderProgram, parent * modelMatrix, UNIFORM_MODEL_MATRIX_NAME);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

}

void Cube::loadCube() {
    const Vertex vertices[] = {
            Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.6, 0.3, 0.3)),
            Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.3, 0.6, 0.3)),
            Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.3, 0.3, 0.6)),
            Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.6, 0.6, 0.3)),

            Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.3, 0.6, 0.6)),
            Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.6, 0.3, 0.6)),
            Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.6, 0.6, 0.6)),
            Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.3, 0.3, 0.3)),
    };

    unsigned int indices[] = {
            0, 2, 3, // Top
            0, 3, 1,

            2, 6, 7, // Front
            2, 7, 3,

            3, 7, 5, // Right
            3, 5, 1,

            0, 4, 6, // Left
            0, 6, 2,

            1, 5, 4, // Back
            1, 4, 0,

            6, 4, 5, // Bottom
            6, 5, 7,
    };

    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &cubeIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);
}




