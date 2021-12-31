#include <algorithm>
#include <cmath>

#include "Triangle.h"
#include "math/math.h"
#include "BoundingBox.h"
#include "OpenGL.h"

Triangle::Triangle(const vec2& a, const vec2& b, const vec2& c): a{a}, b{b}, c{c} {}

vec3 Triangle::getBarycentricCoords(const vec2& point) const {
  vec3 bCoords;
  float totalArea = area(); 

  bCoords.x = Triangle::getArea(point, b, c) / totalArea;
  bCoords.y = Triangle::getArea(point, a, c) / totalArea;
  bCoords.z = 1.0f - bCoords.x - bCoords.y;

  return bCoords; 
}

float Triangle::interpolateFloat(const vec3& vals, const vec2& point) const {
  vec3 bCoords = getBarycentricCoords(point);

  return vec3::dot(bCoords, vals);
}

bool Triangle::containsPoint(const vec2& point) const {
  // Add top-left test
  vec3 bCoords = getBarycentricCoords(point);

  return bCoords.x >= 0 && bCoords.y >= 0 && bCoords.z >= 0; 
}

float Triangle::area() const {
  return Triangle::getArea(a, b, c);
}

// creating a bounding box struct? 
BoundingBox Triangle::getBoundingBox() const {
  return BoundingBox {
    .minX = (int) std::min({a.x, b.x, c.x}),
    .maxX = (int) std::max({a.x, b.x, c.x}),

    .minY = (int) std::min({a.y, b.y, c.y}),
    .maxY = (int) std::max({a.y, b.y, c.y})
  }; 
}

std::vector<vec2> Triangle::getCoveredPoints(const Triangle& triangle, const BoundingBox& bbox) {
  BoundingBox triangleBBox = triangle.getBoundingBox();

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

      if (point.x <= 0 || point.x >= CONST::WW)
        assert(false);

      if ((triangleContainsPnt = triangle.containsPoint(pointCenter))) {
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
