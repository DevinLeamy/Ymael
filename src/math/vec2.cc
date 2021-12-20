#include <memory>
#include <cmath>
#include <iostream>

#include "math/vec2.h"

vec2::vec2(double x, double y): x{x}, y{y} {}

vec2::vec2(const vec2& other): x{other.x}, y{other.y} {}
vec2::vec2(vec2&& other): x{std::move(other.x)}, y{std::move(other.y)} {}

vec2& vec2::operator=(const vec2& other) {
  x = other.x;
  y = other.y;

  return *this;
}

vec2& vec2::normalize() {
  double len = length();
  x /= len;
  y /= len;

  return *this;
}

vec2& vec2::scale(double s) {
  x *= s;
  y *= s;

  return *this;
}

std::ostream& operator<<(std::ostream &os, const vec2& vec) {
  os << "(vec2) x: " << vec.x << ", y: " << vec.y << std::endl;
  return os;
}

double vec2::length() const {
  return sqrt(x * x + y * y);
}

vec2 vec2::add(const vec2& left, const vec2& right) {
  return left + right;
}

vec2 vec2::sub(const vec2& left, const vec2& right) {
  return left - right;
}

vec2 vec2::lerp(const vec2& start, const vec2& end, double t) {
  vec2 diff = end - start;
  return start + diff * t;
}

double vec2::dot(const vec2& left, const vec2& right) {
  return left.x * right.x + left.y * right.y;
}

double vec2::angle(const vec2& left, const vec2& right) {
  double cosA = dot(left, right) / (left.length() * right.length());
  return acos(cosA);
}

double vec2::dist(const vec2& left, const vec2& right) {
  double dx = right.x - left.x;
  double dy = right.y - left.y;

  return sqrt(dx * dx + dy * dy);
}

vec2 vec2::getNormalized(const vec2 &vec) {
  double len = vec.length();

  vec2 res;
  res.x = vec.x / len;
  res.y = vec.y / len;
  
  return res;
}


vec2 &vec2::operator+=(const vec2& right) {
  x += right.x;
  y += right.y;

  return *this;
}

vec2 &vec2::operator-=(const vec2& right) {
  x -= right.x;
  y -= right.y;

  return *this;
}


vec2 vec2::operator+(const vec2& right) const {
  vec2 res;
  res.x = x + right.x;
  res.y = y + right.y;

  return res;
}

vec2 vec2::operator-(const vec2& right) const {
  vec2 res;
  res.x = x - right.x;
  res.y = y - right.y;

  return res;
}

vec2 vec2::operator*(double s) const {
  vec2 res;
  res.x = x * s;
  res.y = y * s;

  return res;
}
