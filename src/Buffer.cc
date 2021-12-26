#include <vector>

#include "Buffer.h"
#include "math/math.h"

Buffer::Buffer(size_t itemCnt, size_t itemSize): itemSize{itemSize},
  data{std::vector<float>(itemCnt * itemSize)} {}

Buffer::Buffer(std::vector<float> data, int itemSize): itemSize{itemSize}, data{data} {}

void Buffer::bind(vec2& vec) { bind(vec.toVector()); }
void Buffer::bind(vec3& vec) { bind(vec.toVector()); }
void Buffer::bind(vec4& vec) { bind(vec.toVector()); }

void Buffer::get(size_t itemIndex, vec2& res) const { res = vec2(get(itemIndex, 2)); }
void Buffer::get(size_t itemIndex, vec3& res) const { res = vec3(get(itemIndex, 3)); }
void Buffer::get(size_t itemIndex, vec4& res) const { res = vec4(get(itemIndex, 4)); }

void Buffer::set(size_t itemIndex, vec2& vec) { set(itemIndex, vec.toVector()); }
void Buffer::set(size_t itemIndex, vec3& vec) { set(itemIndex, vec.toVector()); }
void Buffer::set(size_t itemIndex, vec4& vec) { set(itemIndex, vec.toVector()); }

float getRawFloat(size_t rawIndex) const { return data[rawIndex]; }

void Buffer::setRawFloat(size_t rawIndex, float val) { data[rawIndex] = val; }

size_t Buffer::rawSize() const { return data.size(); }
size_t Buffer::size() const { return rawSize() / itemSize; }


void bind(const std::vector<float> vals) {
  for (float val : vals)
    data[rawIndex++] = val;
}

const std::vector<float>& get(size_t itemIndex, size_t floatCnt) {
  std::vector<float> vals;
  size_t rawIndex = this->rawIndex(itemIndex);
  for (size_t i = 0; i < floatCnt; ++i)
    vals.push_back(data[rawIndex + i]);
  
  return vals;
}

void set(size_t itemIndex, const std::vector<float>& vals) {
  size_t rawIndex = this->rawIndex(itemIndex);
  for (float val : vals) 
    data[rawIndex++] = val;
}

void Buffer::rawIndex(size_t itemIndex) const {
  return itemIndex * itemSize;
}
