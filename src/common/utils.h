#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <unordered_map>

using glm::vec3;
using glm::vec2;
using glm::mat4;

using std::unordered_map;


namespace s8 {
    struct Vertex {
        vec3 position;
        vec3 color;
        vec2 uv;
        vec3 normal;

        Vertex(vec3 position, vec3 color) :
                position{position},
                color{color},
                uv{vec2(0)},
                normal{vec3(0, 1, 0)} {}

        Vertex(vec3 position, vec3 color, vec2 uv, vec3 normal) :
                position{position},
                color{color},
                uv{uv},
                normal{normal} {}

        Vertex(vec3 position, vec2 uv, vec3 normal) :
                position{position},
                color{vec3(0)},
                uv{uv},
                normal{normal} {}
    };

    struct Rotation {
        float angle;
        vec3 axis;

        Rotation() :
                angle{0},
                axis{vec3(1)} {}

        Rotation(float angle, vec3 axis) :
                angle{angle},
                axis{axis} {}
    };

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


    GLFWwindow *init();

    GLuint loadShaders(const char *vertexFilePath, const char *fragmentFilePath);
    GLuint loadTexture(const char *textureFilePath);

    template<class K, class V>
    bool hasKey(unordered_map<K, V> map, K value) {
        return map.find(value) != map.end();
    }

    void setUniform(GLuint shaderProgram, mat4 value, const char *name);
    void setUniform(GLuint shaderProgram, vec3 value, const char *name);
    void setUniform(GLuint shaderProgram, vec2 value, const char *name);
    void setUniform(GLuint shaderProgram, bool value, const char *name);
    void setUniform(GLuint shaderProgram, int value, const char *name);

    float rng(float min, float max);
    float rng();

}


namespace std {
    using s8::ModelData;
    using s8::CubeConfig;

    template<>
    struct hash<s8::CubeConfig> {
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
