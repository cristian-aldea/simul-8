#include "RenderedModel.h"

#include "../common/constants.h"
#include "../common/utils.h"

using simul8::setUniform;

RenderedModel::RenderedModel(GLuint shader)
        : shader{shader}, Model() {}

void RenderedModel::draw(mat4 parent) {
    glBindVertexArray(getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, getVBO());

    mat4 mvp = parent * getMVPMatrix();

    setUniform(shader, mvp, UNIFORM_MODEL_MATRIX_NAME);

    glDrawArrays(GL_TRIANGLES, 0, getNumVertices());
}
