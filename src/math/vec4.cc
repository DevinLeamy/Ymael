#include <memory>
#include <cmath>
#include <iostream>

#include "math/vec4.h"

vec4::vec4(double x, double y, double z, double w): x{x}, y{y}, z{z}, w{w} {}

vec4::vec4(const vec4& other): x{other.x}, y{other.y}, z{other.z}, w{other.w} {}

vec4& vec4::operator=(const vec4& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;

  return *this;
}

vec4& vec4::normalize() {
  double len = length();
  x /= len;
  y /= len;
  z /= len;
  w /= len;

  return *this;
}

vec4& vec4::scale(double s) {
  x *= s;
  y *= s;
  z *= s;
  w *= s;

  return *this;
}

std::ostream& operator<<(std::ostream &os, const vec4& vec) {
  os << "(vec4) x: " << vec.x << 
  ", y: " << vec.y << 
  ", z: " << vec.z << 
  ", w: " << vec.w << std::endl;

  return os;
}

double vec4::length() const {
  return sqrt(x * x + y * y + z * z + w * w);
}

vec4 vec4::add(const vec4& left, const vec4& right) {
  return left + right;
}

vec4 vec4::sub(const vec4& left, const vec4& right) {
  return left - right;
}

vec4 vec4::lerp(const vec4& start, const vec4& end, double t) {
  vec4 diff = end - start;

  return start + diff * t;
}

double vec4::dot(const vec4& left, const vec4& right) {
  return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

double vec4::angle(const vec4& left, const vec4& right) {
  double cosA = dot(left, right) / (left.length() * right.length());
  return acos(cosA);
}

double vec4::dist(const vec4& left, const vec4& right) {
  double dx = right.x - left.x;
  double dy = right.y - left.y;
  double dz = right.z - left.z;
  double dw = right.w - left.w;


  return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

vec4 vec4::getNormalized(const vec4 &vec) {
  double len = vec.length();

  vec4 res;
  res.x = vec.x / len;
  res.y = vec.y / len;
  res.z = vec.z / len;
  res.w = vec.z / len;
  
  return res;
}


vec4 &vec4::operator+=(const vec4& right) {
  x += right.x;
  y += right.y;
  z += right.z;
  w += right.w;

  return *this;
}

vec4 &vec4::operator-=(const vec4& right) {
  x -= right.x;
  y -= right.y;
  z -= right.z;
  w -= right.w;

  return *this;
}


vec4 vec4::operator+(const vec4& right) const {
  vec4 res;
  res.x = x + right.x;
  res.y = y + right.y;
  res.z = z + right.z;
  res.w = w + right.w;

  return res;
}

vec4 vec4::operator-(const vec4& right) const {
  vec4 res;
  res.x = x - right.x;
  res.y = y - right.y;
  res.z = z - right.z;
  res.w = w - right.w;

  return res;
}

vec4 vec4::operator*(double s) const {
  vec4 res;
  res.x = x * s;
  res.y = y * s;
  res.z = z * s;
  res.w = w * s;

  return res;
}
