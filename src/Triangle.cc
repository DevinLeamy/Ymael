#include <algorithm>
#include <cmath>
#include <cassert>

#include "Triangle.h"
#include "math/math.h"
#include "BoundingBox.h"
#include "OpenGL.h"

Triangle::Triangle() {}
Triangle::Triangle(const vec2& a, const vec2& b, const vec2& c): a{a}, b{b}, c{c} {}

vec3 Triangle::getBarycentricCoords(const vec2& point) const {
  vec3 bCoords;
  float totalArea = area(); 

  bCoords.x = Triangle::getArea(point, b, c) / totalArea;
  bCoords.y = Triangle::getArea(a, point, c) / totalArea;
  bCoords.z = Triangle::getArea(a, b, point) / totalArea;

  return bCoords; 
}

float Triangle::interpolateFloat(const vec3& vals, const vec2& point) const {
  vec3 bCoords = getBarycentricCoords(point);

  return vec3::dot(bCoords, vals);
}

float edgeFunction(const vec2 &a, const vec2 &b, const vec2 &point) { 
    return (point.x - a.x) * (b.y - a.y) - (point.y - a.y) * (b.x - a.x); 
} 

bool Triangle::containsPoint(const vec2& point) const {
  float denominator = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));

  float wa = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / denominator;
  float wb = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / denominator;

  float wc = 1.0f - wa - wb;

  return (wa < -0.001) == (wb < -0.001) && (wb < -0.001) == (wc < -0.001);
}

float Triangle::area() const {
  return Triangle::getArea(a, b, c);
}

BoundingBox Triangle::getBoundingBox() const {
  return BoundingBox {
    .minX = (int) std::min({a.x, b.x, c.x}),
    .maxX = (int) std::max({a.x, b.x, c.x}),

    .minY = (int) std::min({a.y, b.y, c.y}),
    .maxY = (int) std::max({a.y, b.y, c.y})
  }; 
}

std::vector<vec2> Triangle::getCoveredPoints(Triangle* triangle, const BoundingBox& bbox) {
  BoundingBox triangleBBox = triangle->getBoundingBox();

  int minX = std::max(triangleBBox.minX, bbox.minX);
  int maxX = std::min(triangleBBox.maxX, bbox.maxX);

  int minY = std::max(triangleBBox.minY, bbox.minY);
  int maxY = std::min(triangleBBox.maxY, bbox.maxY);

  std::vector<vec2> covered;

  // optimize
  for (int x = minX; x < maxX; ++x) {
    bool prevWasCovered = false;
    for (int y = minY; y < maxY; ++y) {
      vec2 pointCenter(x + 0.5f, y + 0.5f);
      vec2 point(x, y);

      bool triangleContainsPnt; 

      if ((triangleContainsPnt = triangle->containsPoint(pointCenter))) {
        covered.push_back(point);
        prevWasCovered = true;
      }

      if (prevWasCovered && !triangleContainsPnt)
        break;
    }
  }

  return covered;
}

float Triangle::getArea(const vec2& a, const vec2& b, const vec2& c) {
  return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) * 0.5f;
}
