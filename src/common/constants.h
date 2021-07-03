#pragma once

#include <glm/glm.hpp>

using glm::mat4;

const mat4 MAT4_I = mat4(1);

const char *const UNIFORM_MODEL_MATRIX_NAME = "modelMatrix";
const char *const UNIFORM_VIEW_MATRIX_NAME = "viewMatrix";
const char *const UNIFORM_PROJECTION_MATRIX_NAME = "projectionMatrix";
