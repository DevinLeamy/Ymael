#pragma once

#include <iostream>

class vec4 {
public:
  float x, y, z, w;

  vec4(float x = 0, float y = 0, float z = 0, float w = 0);

  vec4(const vec4& other);

  vec4 &operator=(const vec4& other);
  float& operator[](int index);
  const float& operator[](int index) const;

  friend std::ostream& operator<<(std::ostream& os, const vec4& vec); 
  
  ~vec4() = default;

  // create vector of magnitude 1 
  vec4 &normalize();
  vec4 &scale(float s);

  // magnitude
  float length() const;

  static vec4 add(const vec4& left, const vec4& right);
  static vec4 sub(const vec4& left, const vec4& right);

  // linear interpolation 
  static vec4 lerp(const vec4& start, const vec4& end, float t);

  // dot product: "similarily" of two vectors
  static float dot(const vec4& left, const vec4& right);

  // angle between two vectors
  static float angle(const vec4& left, const vec4& right);

  // distance between two vector end points
  static float dist(const vec4& left, const vec4& right);

  static vec4 getNormalized(const vec4 &v);

  vec4 &operator+=(const vec4& right);
  vec4 &operator-=(const vec4& right);

  vec4 operator+(const vec4& right) const;
  vec4 operator-(const vec4& right) const;

  vec4 operator*(float s) const;
};
