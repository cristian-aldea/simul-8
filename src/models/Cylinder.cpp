#include "Cylinder.h"

#include <vector>

#include "../common/utils.h"
#include "../common/constants.h"

using std::vector;

using glm::vec4;
using glm::vec2;

using simul8::Vertex;
using simul8::setUniform;

unsigned int Cylinder::vao = 0;
unsigned int Cylinder::vbo = 0;
int Cylinder::numVertices = 0;

Cylinder::Cylinder(GLuint shader)
        : RenderedModel(shader) {}

void Cylinder::drawVertices() const {
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Cylinder::loadModel() {
    // This method generates cylinder vertices mathematically and populates the VBO with the generated data

    vector<vec4> positions; // Points on the circle of the front/back of the cylinder
    int precision = 50; // Number of points of the circle, higher -> better circle

    for (int i = 0; i < precision; ++i) {
        float angle = 360.0f / precision * i;
        float x = cosf(glm::radians(angle)) * 0.5f;
        float y = sinf(glm::radians(angle)) * 0.5f;
        positions.emplace_back(x, y, 0, glm::radians(angle));
    }
    vector<Vertex> vertices;

    float halfHeight = 0.5f;
    vec3 color = vec3(1);
    int size = positions.size();

    // Triangle vertices for front circle
    for (int i = 0; i < size; ++i) {
        vertices.push_back(Vertex(vec3(0, 0, halfHeight), color, vec2(0, 0), vec3(0, 0, 1)));
        vertices.push_back(Vertex(vec3(positions[i].x, positions[i].y, halfHeight), color, vec2(positions[i].x, positions[i].y), vec3(0, 0, 1)));
        vertices.push_back(Vertex(vec3(positions[(i + 1) % size].x, positions[(i + 1) % size].y, halfHeight), color,
                                  vec2(positions[(i + 1) % size].x, positions[(i + 1) % size].y), vec3(0, 0, 1)));
    }

    // Triangle vertices for the back circle
    for (int i = 0; i < size; ++i) {
        vertices.emplace_back(vec3(positions[(i + 1) % size].x, positions[(i + 1) % size].y, -halfHeight), color,
                              vec2(positions[(i + 1) % size].x, positions[(i + 1) % size].y), vec3(0, 0, -1));
        vertices.emplace_back(vec3(positions[i].x, positions[i].y, -halfHeight), color, vec2(positions[i].x, positions[i].y), vec3(0, 0, -1));
        vertices.emplace_back(vec3(0, 0, -halfHeight), color, vec2(0, 0), vec3(0, 0, -1));
    }

    // triangle vertices for the side of the cylinder
    for (int i = 0; i < size; ++i) {
        // Both of these triangle form a rectangle from that connect positions[i] and positions[i+1] of the two circles
        vertices.emplace_back(vec3(positions[i].x, positions[i].y, halfHeight), color, vec2(halfHeight, positions[i][3] * halfHeight), positions[i]);
        vertices.emplace_back(vec3(positions[i].x, positions[i].y, -halfHeight), color, vec2(-halfHeight, positions[i][3] * halfHeight),
                              positions[i]);
        vertices.emplace_back(vec3(positions[(i + 1) % size].x, positions[(i + 1) % size].y, halfHeight), color,
                              vec2(halfHeight, positions[(i + 1) % size][3] * halfHeight), positions[(i + 1) % size]);

        vertices.emplace_back(vec3(positions[i].x, positions[i].y, -halfHeight), color, vec2(-halfHeight, positions[i][3] * halfHeight),
                              positions[i]);
        vertices.emplace_back(vec3(positions[(i + 1) % size].x, positions[(i + 1) % size].y, -halfHeight), color,
                              vec2(-halfHeight, positions[(i + 1) % size][3] * halfHeight), positions[(i + 1) % size]);
        vertices.emplace_back(vec3(positions[(i + 1) % size].x, positions[(i + 1) % size].y, halfHeight), color,
                              vec2(halfHeight, positions[(i + 1) % size][3] * halfHeight), positions[(i + 1) % size]);

    }

    numVertices = vertices.size();

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

}

GLuint Cylinder::getVAO() const {
    return vao;
}

GLuint Cylinder::getVBO() const {
    return vbo;
}

GLsizei Cylinder::getNumVertices() const {
    return numVertices;
}
