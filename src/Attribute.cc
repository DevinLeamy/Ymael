#include <cassert>
#include <vector>
#include <algorithm>

#include "Attribute.h"
#include "utility.h"

Attribute::Attribute(size_t size): size{size}, data{std::vector<float>(size, 0.0f)} {}
Attribute::Attribute(size_t size, const std::vector<float>& data): size{size}, data{data} {}

size_t Attribute::getSize() const { 
  return size;
}

float Attribute::getFloat(int index) const { 
  assert(index < size);

  return data[index]; 
}

void Attribute::setFloat(int index, float value) {
  assert(index < size);

  data[index] = value;
}

void Attribute::set(const std::vector<float> &data) {
  assert(data.size() == size);

  // std::swap(this->data, data);
  for (size_t i = 0; i < size; ++i)
    this->data[i] = data[i];
}

const std::vector<float>& Attribute::get() const {
  return data;
}
