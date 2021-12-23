#include "shaders/VertexShader.h"


VertexShader::VertexShader(): modelMatrix{mat4::identity()}, viewMatrix{mat4::identity()}, 
  projectionMatrix{mat4::identity()}
{}

void VertexShader::setUniform(MatrixType mt, mat4 matrix) {
  if (mt == MODEL_MATRIX)
    modelMatrix = matrix;
  else if (mt == VIEW_MATRIX)
    viewMatrix = matrix;
  else if (mt == PROJECTION_MATRIX)
    projectionMatrix = matrix;
}
