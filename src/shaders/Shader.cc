#include "VertexArrayObject.h"
#include "shaders/Shader.h"

void Shader::setInputAttr(int attrIndex, int itemSize) {
  inputBufferMap[attrIndex] = itemSize;
}

const std::map<int, int>& Shader::getInputBufferMap() const {
  return inputBufferMap;
}

const std::map<int, int>& Shader::getOutputBufferMap() const {
  return outputBufferMap;
}

void Shader::setOutputAttr(int attrIndex, int itemSize) {
  outputBufferMap[attrIndex] = itemSize;
}
