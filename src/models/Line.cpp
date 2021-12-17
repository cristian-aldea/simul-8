#include "Line.h"

#include "../common/utils.h"
#include "../common/globals.h"

using s8::Vertex;
using s8::defaultTexture;

GLsizei Line::numVertices = 0;
GLuint Line::vao = 0;
GLuint Line::vbo = 0;
bool Line::loaded = false;

Line::Line(GLuint shader)
        : RenderedModel(shader, defaultTexture) {

    loadModel();
}

void Line::drawVertices() const {
    glDrawArrays(GL_LINES, 0, numVertices);
}


void Line::loadModel() {
    if (!loaded) {
        loaded = true;
    } else {
        return;
    }

    vector<Vertex> vertices = {
            Vertex(vec3(0, 0, 0), vec3(1, 0, 0)),
            Vertex(vec3(1, 0, 0), vec3(1, 0, 0)),
    };

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

GLuint Line::getVAO() const {
    return vao;
}

GLuint Line::getVBO() const {
    return vbo;
}
