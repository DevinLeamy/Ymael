#include "shaders/VertexShader.h"


VertexShader::VertexShader(): Shader{}, 
  modelMatrix{mat4::identityM()}, 
  viewMatrix{mat4::identityM()}, 
  projectionMatrix{mat4::identityM()}
{}

void VertexShader::setUniform(MatrixType mt, mat4 matrix) {
  if (mt == MODEL_MATRIX)
    modelMatrix = matrix;
  else if (mt == VIEW_MATRIX)
    viewMatrix = matrix;
  else if (mt == PROJECTION_MATRIX)
    projectionMatrix = matrix;
}
