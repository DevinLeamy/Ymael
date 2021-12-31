#pragma once

#include <vector>

class Attribute {
public:
  Attribute(size_t size);
  Attribute(size_t size, const std::vector<float>& data);

  size_t getSize() const;

  float getFloat(int index) const;
  void setFloat(int index, float value);

  void set(const std::vector<float> &data);
  const std::vector<float>& get() const;

  ~Attribute() = default;

private:
  size_t size; 
  std::vector<float> data;
};
