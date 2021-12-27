#pragma once

#include <memory>
#include <vector>
#include <map>

#include "VertexArrayObject.h"

class Shader {
public:
  Shader() = default;
  virtual ~Shader() = default;
  virtual void run(VertexArrayObject* inStream, VertexArrayObject* outStream, std::vector<int> attrIndices) = 0;

  const std::map<int, int>& getInputBufferMap() const; 
  const std::map<int, int>& getOutputBufferMap() const; 
protected:
  // attributeIndex -> itemSize (everything is single-buffer)
  std::map<int, int> inputBufferMap;
  std::map<int, int> outputBufferMap;
};
