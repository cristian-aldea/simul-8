#include "Sphere.h"

#include "../common/globals.h"

using s8::defaultTexture;
using s8::Vertex;

GLsizei Sphere::numVertices = 0;
GLsizei Sphere::numIndices = 0;
GLuint Sphere::vao = 0;
GLuint Sphere::vbo = 0;
GLuint Sphere::ibo = 0;
bool Sphere::loaded = false;

Sphere::Sphere() : Sphere(defaultTexture) {}

Sphere::Sphere(GLuint texture) : RenderedModel(texture) {
    loadModel();
}

void Sphere::drawVertices() const {
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
}

void Sphere::loadModel() {
    if (!loaded) {
        loaded = true;
    } else {
        return;
    }
    // Code for vertices and indices based on http://www.songho.ca/opengl/gl_sphere.html
    const float PI = acos(-1);
    int sectorCount = 50;
    int stackCount = 50;
    float radius = 0.5f;

    float x, y, z, xy;                              // vertex position
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;
    vec3 color(1);

    vector<s8::Vertex> vertices;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

            // vertex tex coord (s, t) range between [0, 1]
            s = (float) j / sectorCount;
            t = (float) i / stackCount;

            vec3 position(x, y, z);
            vertices.emplace_back(position, color, vec2(s, t), normalize(position));
        }
    }

    std::vector<unsigned int> indices;
    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    numVertices = vertices.size();
    numIndices = indices.size();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(vec3) + sizeof(vec2)));
    glEnableVertexAttribArray(3);
}

GLuint Sphere::getVAO() const {
    return vao;
}

GLuint Sphere::getVBO() const {
    return vbo;
}


