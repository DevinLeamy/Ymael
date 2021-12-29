#pragma once

#include "shaders/Shader.h"
#include "math/mat4.h"

enum MatrixType {
  MODEL_MATRIX, // model space -> world space
  VIEW_MATRIX,  // world space -> view space
  PROJECTION_MATRIX // view space -> clip space
};

class VertexShader: public Shader {
public:
  VertexShader();

  void setUniform(MatrixType mt, mat4 matrix);
protected:
  mat4 modelMatrix;
  mat4 viewMatrix;
  mat4 projectionMatrix;
};

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

