#include "VertexArrayObject.h"
#include "shaders/Shader.h"

const std::map<int, int>& Shader::getInputBufferMap() const {
  return inputBufferMap;
}

const std::map<int, int>& Shader::getOutputBufferMap() const {
  return outputBufferMap;
}
