#pragma once

#include "Buffer.h"

class VertexBufferObject: public Buffer {
public:
  VertexBufferObject(size_t floatCount, size_t size): Buffer{floatCount, size} {}
  VertexBufferObject(std::vector<float> data, std::vector<int> indices): Buffer{data, indices} {}
};
