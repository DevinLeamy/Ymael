#pragma once

#include <iostream>
#include <vector>

class vec3 {
public:
  float x, y, z;

  vec3(const std::vector<float>& vals);
  vec3(float x = 0, float y = 0, float z = 0);

  vec3(const vec3& other);

  vec3 &operator=(const vec3& other);
  float& operator[](int index);

  friend std::ostream& operator<<(std::ostream& os, const vec3& vec); 
  
  ~vec3() = default;

  // create vector of magnitude 1 
  vec3 &normalize();
  vec3 &scale(float s);

  // magnitude
  float length() const;

  static vec3 add(const vec3& left, const vec3& right);
  static vec3 sub(const vec3& left, const vec3& right);

  // cross product: vector orthogonal to left and right
  static vec3 cross(const vec3& left, const vec3& right);

  // linear interpolation 
  static vec3 lerp(const vec3& start, const vec3& end, float t);

  // dot product: "similarily" of two vectors
  static float dot(const vec3& left, const vec3& right);

  // angle between two vectors
  static float angle(const vec3& left, const vec3& right);

  // distance between two vector end points
  static float dist(const vec3& left, const vec3& right);

  static vec3 getNormalized(const vec3 &v);


  vec3 &operator+=(const vec3& right);
  vec3 &operator-=(const vec3& right);

  vec3 operator+(const vec3& right) const;
  vec3 operator-(const vec3& right) const;

  vec3 operator*(float s) const;

  const std::vector<float> &toVector() const;
};
