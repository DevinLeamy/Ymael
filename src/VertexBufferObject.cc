#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(size_t itemCnt, size_t itemSize): Buffer{itemCnt, itemSize} {}
VertexBufferObject::VertexBufferObject(std::vector<float> data, size_t itemSize): Buffer{data, itemSize} {}
