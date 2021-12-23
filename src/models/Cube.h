#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


#include <map>
#include <unordered_map>
#include <string>

#include "RenderedModel.h"

using glm::mat4;
using glm::vec3;

using std::hash;
using std::size_t;

using s8::CubeConfig;
using s8::ModelData;

class Cube : public RenderedModel {
public:
    explicit Cube();
    Cube(GLuint texture);
    Cube(vec3 size);
    Cube(GLuint texture, vec3 size);
private:
    static std::unordered_map<CubeConfig, ModelData> dataMap;

    GLsizei numVertices = 0;
    GLuint vao = 0;
    GLuint vbo = 0;

    void drawVertices() const override;
    void loadModel(CubeConfig config);

    GLuint getVAO() const override;
    GLuint getVBO() const override;
};
