#pragma once
/*
(vertex input)
VERTEX SHADER
(rasterizer)

Role:
- To take in vertex attributes and convert them into triangle
  primitives in screen space.

- Handles vertices individually, and MUST compute a position.

Notes:

*/

#include "shaders/Shader.h"
#include "math/mat4.h"

enum MatrixType {
  MODEL_MATRIX,
  VIEW_MATRIX,
  PROJECTION_MATRIX
};

class VertexShader: public Shader {
public:
  VertexShader();

  void setUniform(MatrixType mt, mat4 matrix);
private:
  mat4 modelMatrix;
  mat4 viewMatrix;
  mat4 projectionMatrix;
};
