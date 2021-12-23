#include "Cube.h"

#include <unordered_map>
#include <glad/glad.h>
#include "glm/gtx/string_cast.hpp"

#include "../common/globals.h"

using glm::vec3;

using s8::Vertex;
using s8::setUniform;
using s8::rng;
using s8::hasKey;
using s8::defaultTexture;

std::unordered_map<CubeConfig, ModelData> Cube::dataMap;

Cube::Cube() : Cube(defaultTexture, vec3(1)) {}

Cube::Cube(GLuint texture) : Cube(texture, vec3(1)) {}

Cube::Cube(vec3 size)
        : Cube(defaultTexture, size) {}

Cube::Cube(GLuint texture, vec3 size)
        : RenderedModel(texture) {
    CubeConfig config(size);

    loadModel(config);
}


void Cube::drawVertices() const {
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

#include <iostream>

void Cube::loadModel(CubeConfig config) {
    if (hasKey(dataMap, config)) {
        std::cout << "reuse config: " << glm::to_string(config.scale) << "\n";
        vao = dataMap[config].vao;
        vbo = dataMap[config].vbo;
        numVertices = dataMap[config].numVertices;
        return;
    }

    std::cout << "new config: " << glm::to_string(config.scale) << "\n";
    float xScale = config.scale.x;
    float yScale = config.scale.y;
    float zScale = config.scale.z;

    vector<Vertex> extra;
    vector<Vertex> vertices = {
            // Front
            Vertex(vec3(-1, -1, 1), vec2(0, 0), vec3(0, 0, 1)),
            Vertex(vec3(1, -1, 1), vec2(xScale, 0), vec3(0, 0, 1)),
            Vertex(vec3(1, 1, 1), vec2(xScale, yScale), vec3(0, 0, 1)),
            Vertex(vec3(-1, -1, 1), vec2(0, 0), vec3(0, 0, 1)),
            Vertex(vec3(1, 1, 1), vec2(xScale, yScale), vec3(0, 0, 1)),
            Vertex(vec3(-1, 1, 1), vec2(0, yScale), vec3(0, 0, 1)),

            // Top
            Vertex(vec3(-1, 1, 1), vec2(0, 0), vec3(0, 1, 0)),
            Vertex(vec3(1, 1, 1), vec2(xScale, 0), vec3(0, 1, 0)),
            Vertex(vec3(1, 1, -1), vec2(xScale, zScale), vec3(0, 1, 0)),
            Vertex(vec3(-1, 1, 1), vec2(0, 0), vec3(0, 1, 0)),
            Vertex(vec3(1, 1, -1), vec2(xScale, zScale), vec3(0, 1, 0)),
            Vertex(vec3(-1, 1, -1), vec2(0, zScale), vec3(0, 1, 0)),

            // Right
            Vertex(vec3(1, -1, 1), vec2(0, 0), vec3(1, 0, 0)),
            Vertex(vec3(1, -1, -1), vec2(zScale, 0), vec3(1, 0, 0)),
            Vertex(vec3(1, 1, -1), vec2(zScale, yScale), vec3(1, 0, 0)),
            Vertex(vec3(1, -1, 1), vec2(0, 0), vec3(1, 0, 0)),
            Vertex(vec3(1, 1, -1), vec2(zScale, yScale), vec3(1, 0, 0)),
            Vertex(vec3(1, 1, 1), vec2(0, yScale), vec3(1, 0, 0)),
    };

    // Calculating other half of cube
    for (auto &vertex: vertices) {
        vertex.position *= 0.5;
        Vertex copy = vertex;

        copy.normal *= -1;

        if (copy.normal.z != 0 || copy.normal.x != 0) {
            copy.position.z *= -1;
            copy.position.x *= -1;
        } else if (copy.normal.y != 0) {
            copy.position.z *= -1;
            copy.position.y *= -1;
        }
        extra.push_back(copy);

    }

    vertices.insert(vertices.end(), extra.begin(), extra.end());

    numVertices = vertices.size();

    for (auto &vertex: vertices) {
        vertex.position.x *= config.scale.x;
        vertex.position.y *= config.scale.y;
        vertex.position.z *= config.scale.z;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3) + sizeof(vec2)));
    glEnableVertexAttribArray(3);

    dataMap[config] = ModelData(vao, vbo, numVertices);
}

GLuint Cube::getVAO() const {
    return vao;
}

GLuint Cube::getVBO() const {
    return vao;
}

