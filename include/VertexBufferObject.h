#pragma once

#include "Buffer.h"


class VertexBufferObject: public Buffer {
public:
  VertexBufferObject(size_t itemCnt, size_t itemSize);
  VertexBufferObject(std::vector<float> data, size_t itemSize);
};
