#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <map>
#include <unordered_map>
#include <string>

#include "RenderedModel.h"

using glm::mat4;
using glm::vec3;

using std::hash;
using std::size_t;

struct CubeConfig {
    vec3 scale;
    vec3 color;

    CubeConfig(vec3 size, vec3 color) : scale{size}, color{color} {}

    bool operator==(const CubeConfig &o) const {
        return scale == o.scale && color == o.color;
    }
};

struct ModelData {
    GLuint vao;
    GLuint vbo;

    ModelData() : vao{0}, vbo{0} {}

    ModelData(GLuint vao, GLuint vbo) : vao{vao}, vbo{vbo} {}

    bool operator==(const ModelData &o) const {
        return vao == o.vao && vbo == o.vbo;
    }

    friend void swap(ModelData &first, ModelData &second) {
        using std::swap;

        swap(first.vao, second.vao);
        swap(first.vbo, second.vbo);
    }

    ModelData &operator=(ModelData other) {
        swap(*this, other);

        return *this;
    }
};

namespace std {
    template<>
    struct hash<CubeConfig> {
        size_t operator()(const CubeConfig &k) const {
            using std::hash;
            return hash<vec3>()(k.scale) ^ (hash<vec3>()(k.color) << 1);
        }
    };

    template<>
    struct hash<ModelData> {
        size_t operator()(const ModelData &k) const {
            return hash<GLuint>()(k.vao) ^ (hash<GLuint>()(k.vao) << 1);
        }
    };
}


class Cube : public RenderedModel {
public:
    explicit Cube(GLuint shader);
    Cube(GLuint shader, GLuint texture);
    Cube(GLuint shader, vec3 size, vec3 color);
    Cube(GLuint shader, GLuint texture, vec3 size, vec3 color);
    void loadModel(CubeConfig config);

private:
    static std::unordered_map<CubeConfig, ModelData> dataMap;

    GLsizei numVertices = 0;

    void drawVertices() const override;
    GLsizei getNumVertices() const override;

};
