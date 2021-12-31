#pragma once

#include <vector>

#include "math/math.h"
#include "BoundingBox.h"

class Triangle {
public:
  Triangle(const vec2& a, const vec2& b, const vec2& c);
  ~Triangle() = default;

  vec3 getBarycentricCoords(const vec2& point) const; 
  float interpolateFloat(const vec3& vals, const vec2& point) const; 
  bool containsPoint(const vec2& point) const; 

  BoundingBox getBoundingBox() const;
  static std::vector<vec2> getCoveredPoints(const Triangle& triangle, const BoundingBox& bbox);

  float area() const;

  static float getArea(const vec2& a, const vec2& b, const vec2& c);

private:
  vec2 a;
  vec2 b;
  vec2 c;
};
