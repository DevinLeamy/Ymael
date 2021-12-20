#pragma once

#include <iostream>

class vec4 {
public:
  double x, y, z, w;

  vec4(double x = 0, double y = 0, double z = 0, double w = 0);

  vec4(const vec4& other);

  vec4 &operator=(const vec4& other);

  friend std::ostream& operator<<(std::ostream& os, const vec4& vec); 
  
  ~vec4() = default;

  // create vector of magnitude 1 
  vec4 &normalize();
  vec4 &scale(double s);

  // magnitude
  double length() const;

  static vec4 add(const vec4& left, const vec4& right);
  static vec4 sub(const vec4& left, const vec4& right);

  // linear interpolation 
  static vec4 lerp(const vec4& start, const vec4& end, double t);

  // dot product: "similarily" of two vectors
  static double dot(const vec4& left, const vec4& right);

  // angle between two vectors
  static double angle(const vec4& left, const vec4& right);

  // distance between two vector end points
  static double dist(const vec4& left, const vec4& right);

  static vec4 getNormalized(const vec4 &v);

  vec4 &operator+=(const vec4& right);
  vec4 &operator-=(const vec4& right);

  vec4 operator+(const vec4& right) const;
  vec4 operator-(const vec4& right) const;

  vec4 operator*(double s) const;
};
