#include "Cube.h"

#include <glad/glad.h>

using glm::vec3;

using s8::Vertex;
using s8::setUniform;
using s8::rng;

unsigned int Cube::vao = 0;
unsigned int Cube::vbo = 0;

Cube::Cube(GLuint shader)
        : RenderedModel(shader) {}

GLuint Cube::getVAO() const {
    return vao;
}

GLuint Cube::getVBO() const {
    return vbo;
}

GLsizei Cube::getNumVertices() const {
    return cubeNumVertices;
}

void Cube::drawVertices() const {
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVertices);
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

    for (auto &vertex: vertices) {
        vertex.color = vec3(rng(), rng(), rng());
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cubeNumVertices, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3) + sizeof(vec2)));
    glEnableVertexAttribArray(3);
}

