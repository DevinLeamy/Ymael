#pragma once

#include <memory>
#include <vector>
#include <map>

#include "VertexArrayObject.h"

class Shader {
public:
  Shader() = default;
  virtual ~Shader() = default;
  virtual void run(VertexArrayObject* inStream, VertexArrayObject* outStream, std::vector<std::vector<int>> attrIndices) = 0;
  virtual void run(VertexArrayObject* inStream, VertexArrayObject* outStream, int vertexIndex);

  void setInputAttr(int attrIndex, int itemSize);
  void setOutputAttr(int attrIndex, int itemSize);

  const std::map<int, int>& Shader::getInputBufferMap() const; 
  const std::map<int, int>& Shader::getOutputBufferMap() const; 
private:
  // attributeIndex -> itemSize (everything is single-buffer)
  std::map<int, int> inputBufferMap;
  std::map<int, int> outputBufferMap;
};
