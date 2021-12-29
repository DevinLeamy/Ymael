#include <vector>

#include "Buffer.h"
#include "math/math.h"
#include "utility.h"

Buffer::Buffer(size_t itemCnt, size_t itemSize): itemSize{itemSize},
  data{std::vector<float>(itemCnt * itemSize)} {}

Buffer::Buffer(std::vector<float> data, size_t itemSize): itemSize{itemSize}, data{data} {}

void Buffer::bind(float val) { data[rawIndex++] = val; }
void Buffer::bind(vec2& vec) { bind(vec.toVector()); }
void Buffer::bind(vec3& vec) { bind(vec.toVector()); }
void Buffer::bind(vec4& vec) { bind(vec.toVector()); }

void Buffer::get(size_t itemIndex, float& res) const { res = data[getRawIndex(itemIndex)]; }
void Buffer::get(size_t itemIndex, vec2& res) const { res = vec2(getSegment(itemIndex, 2)); }
void Buffer::get(size_t itemIndex, vec3& res) const { res = vec3(getSegment(itemIndex, 3)); }
void Buffer::get(size_t itemIndex, vec4& res) const { res = vec4(getSegment(itemIndex, 4)); }

void Buffer::set(size_t itemIndex, float val) { data[getRawIndex(itemIndex)] = val; } 
void Buffer::set(size_t itemIndex, vec2& vec) { set(itemIndex, vec.toVector()); }
void Buffer::set(size_t itemIndex, vec3& vec) { set(itemIndex, vec.toVector()); }
void Buffer::set(size_t itemIndex, vec4& vec) { set(itemIndex, vec.toVector()); }

float Buffer::getRawFloat(size_t rawIndex) const { return data[rawIndex]; }

void Buffer::setRawFloat(size_t rawIndex, float val) { data[rawIndex] = val; }

size_t Buffer::getRawSize() const { return data.size(); }
size_t Buffer::getSize() const { return getRawSize() / itemSize; }
size_t Buffer::getItemSize() const { return itemSize; }


void Buffer::bind(const std::vector<float> vals) {
  for (float val : vals)
    data[rawIndex++] = val;
}

std::vector<float> Buffer::getSegment(size_t itemIndex, size_t floatCnt) const {
  std::vector<float> vals;
  size_t rawIndex = getRawIndex(itemIndex);
  for (size_t i = 0; i < floatCnt; ++i)
    vals.push_back(data[rawIndex + i]);
  
  return vals;
}

void Buffer::set(size_t itemIndex, const std::vector<float>& vals) {
  size_t rawIndex = this->getRawIndex(itemIndex);
  for (float val : vals) 
    data[rawIndex++] = val;
}

size_t Buffer::getRawIndex(size_t itemIndex) const {
  return itemIndex * itemSize;
}
