#include <vector>

#include "Buffer.h"
#include "math/math.h"

Buffer::Buffer(std::vector<float> data, std::vector<int> indices):
  data{data}, indices{indices} {}

Buffer::Buffer(size_t floatCount, size_t size):
  data{std::vector<float>(floatCount)}, indices{std::vector<int>(size)} {}

void Buffer::bind(vec2& vec) {
  indices[iIndex] = dIndex;
  data[dIndex++] = vec.x;
  data[dIndex++] = vec.y;
}

void Buffer::bind(vec3& vec) {
  indices[iIndex] = dIndex;
  data[dIndex++] = vec.x;
  data[dIndex++] = vec.y;
  data[dIndex++] = vec.z;
}

void Buffer::get(size_t index, vec2& res) const {
  res.x = data[indices[index]]; 
  res.y = data[indices[index] + 1]; 
}

void Buffer::get(size_t index, vec3& res) const {
  res.x = data[indices[index]]; 
  res.y = data[indices[index] + 1]; 
  res.z = data[indices[index] + 2]; 
}


void Buffer::set(size_t index, vec3& vec) {
  data[indices[index]] = vec.x;
  data[indices[index] + 1] = vec.y;
  data[indices[index] + 2] = vec.z;
}
