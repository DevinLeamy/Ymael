#pragma once

#include <memory>
#include <vector>

#include "VertexArrayObject.h"

class Shader {
  void run(const VertexArrayObject& inStream, const VertexArrayObject& outStream, vector<int> attrIndices);
  void run(const VertexArrayObject& inStream, const VertexArrayObject& outStream, int vertexIndex);
};
