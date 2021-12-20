#include <memory>
#include <cmath>
#include <iostream>

#include "math/vec3.h"

vec3::vec3(double x, double y, double z): x{x}, y{y}, z{z} {}

vec3::vec3(const vec3& other): x{other.x}, y{other.y}, z{other.y} {}

vec3& vec3::operator=(const vec3& other) {
  x = other.x;
  y = other.y;
  z = other.z;

  return *this;
}

vec3& vec3::normalize() {
  double len = length();
  x /= len;
  y /= len;
  z /= len;

  return *this;
}

vec3& vec3::scale(double s) {
  x *= s;
  y *= s;
  z *= s;

  return *this;
}

std::ostream& operator<<(std::ostream &os, const vec3& vec) {
  os << "(vec3) x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << std::endl;
  return os;
}

double vec3::length() const {
  return sqrt(x * x + y * y + z * z);
}

vec3 vec3::add(const vec3& left, const vec3& right) {
  return left + right;
}

vec3 vec3::sub(const vec3& left, const vec3& right) {
  return left - right;
}

vec3 vec3::lerp(const vec3& start, const vec3& end, double t) {
  vec3 diff = end - start;
  return start + diff * t;
}

double vec3::dot(const vec3& left, const vec3& right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

double vec3::angle(const vec3& left, const vec3& right) {
  double cosA = dot(left, right) / (left.length() * right.length());
  return acos(cosA);
}

double vec3::dist(const vec3& left, const vec3& right) {
  double dx = right.x - left.x;
  double dy = right.y - left.y;
  double dz = right.z - left.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

/*
(x) = a2 * b3 - a3 * b2
(y) = a3 * b1 - a1 * b3
(z) = a1 * b2 - a2 * b1
*/
vec3 vec3::cross(const vec3& left, const vec3& right) {
  vec3 res;
  res.x = left.y * right.z - left.z * right.y;
  res.y = left.z * right.x - left.x * right.z;
  res.z = left.x * right.y - left.y * right.x;

  return res;
}

vec3 vec3::getNormalized(const vec3 &vec) {
  double len = vec.length();

  vec3 res;
  res.x = vec.x / len;
  res.y = vec.y / len;
  res.z = vec.z / len;
  
  return res;
}


vec3 &vec3::operator+=(const vec3& right) {
  x += right.x;
  y += right.y;
  z += right.z;

  return *this;
}

vec3 &vec3::operator-=(const vec3& right) {
  x -= right.x;
  y -= right.y;
  z -= right.z;

  return *this;
}


vec3 vec3::operator+(const vec3& right) const {
  vec3 res;
  res.x = x + right.x;
  res.y = y + right.y;
  res.z = z + right.z;

  return res;
}

vec3 vec3::operator-(const vec3& right) const {
  vec3 res;
  res.x = x - right.x;
  res.y = y - right.y;
  res.z = z - right.z;

  return res;
}

vec3 vec3::operator*(double s) const {
  vec3 res;
  res.x = x * s;
  res.y = y * s;
  res.z = z * s;

  return res;
}
