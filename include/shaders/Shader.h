#pragma once

#include <memory>
#include <vector>

#include "VertexArrayObject.h"

class Shader {
public:
  Shader() = default;
  virtual ~Shader() = default;
  virtual void run(VertexArrayObject* inStream, VertexArrayObject* outStream, std::vector<int> attrIndices);
  virtual void run(VertexArrayObject* inStream, VertexArrayObject* outStream, int vertexIndex);
};
