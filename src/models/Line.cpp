#include "Line.h"

#include "../common/utils.h"

using simul8::Vertex;

unsigned int Line::vao = 0;
unsigned int Line::vbo = 0;
int Line::numVertices = 6;

Line::Line(GLuint shader)
        : RenderedModel(shader) {}

void Line::drawVertices() const {
    glDrawArrays(GL_LINES, 0, numVertices);
}

GLuint Line::getVAO() const {
    return vao;
}

GLuint Line::getVBO() const {
    return vbo;
}

GLsizei Line::getNumVertices() const {
    return 6;
}

void Line::loadModel() {
    Vertex vertices[] = {
            Vertex(vec3(0, 0, 0), vec3(1, 0, 0)),
            Vertex(vec3(1, 0, 0), vec3(1, 0, 0)),
            Vertex(vec3(0, 0, 0), vec3(0, 1, 0)),
            Vertex(vec3(0, 1, 0), vec3(0, 1, 0)),
            Vertex(vec3(0, 0, 0), vec3(0, 0, 1)),
            Vertex(vec3(0, 0, 1), vec3(0, 0, 1)),
    };

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
