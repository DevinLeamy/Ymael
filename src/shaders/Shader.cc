#include "shaders/Shader.h"

const std::map<size_t, size_t>& Shader::getInputBufferMap() const {
  return inputBufferMap;
}

const std::map<size_t, size_t>& Shader::getOutputBufferMap() const {
  return outputBufferMap;
}
