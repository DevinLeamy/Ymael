#include <algorithm>

#include "Rasterizer.h"
#include "VertexArrayObject.h"
#include "math/math.h"
#include "OpenGL.h"
#include "utility.h"

void Rasterizer::rasterize(VertexArrayObject *vertexData, int vertices) {

};

void interpolate(VertexArrayObject *vVAO, VertexArrayObject *fVAO, int vIndex) {
  // vertices of the triangle are [vIndex, vIndex + 1, vIndex + 2]
  // assumes position is the first attribute
  vec3 p1, p2, p3;

  vVAO->getAttributeBuffer(0)->get(vIndex, p1);
  vVAO->getAttributeBuffer(0)->get(vIndex + 1, p2);
  vVAO->getAttributeBuffer(0)->get(vIndex + 2, p3);
}

// TODO: optimize
std::vector<vec2> getCoveredPixels(const vec3& p1, const vec3& p2, const vec3& p3) {
  std::vector<vec2> covered;

  int minX = clamp<int>(std::min({p1.x, p2.x, p3.x}), 0, GL->WW);
  int maxX = clamp<int>(std::max({p1.x, p2.x, p3.x}), 0, GL->WW);

  int minY = clamp<int>(std::min({p1.y, p2.y, p3.y}), 0, GL->WH);
  int maxY = clamp<int>(std::max({p1.y, p2.y, p3.y}), 0, GL->WH);

  for (int i = minX; i < maxX; ++i) {
    bool wasInside = false;

    for (int j = minY; j < maxY; ++j) {
      vec2 point{i, j};

      if (insideTriangle(point, p1, p2, p3)) {
        covered.push_back(point);
        wasInside = true;
      } else if (wasInside)
        break;
    }
  }

  return covered;
}

// E(P) > 0 if P is to the right side of the edge
// E(P) = 0 if P is on the edge
// E(P) < 0 if P is to the left side of the edge
bool edgeFunction(const vec2& p, const vec3& v0, const vec3& v1) {
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
  double EP = (p.x - v0.x) * (v1.y - v0.y) -
              (p.y - v0.y) * (v1.x - v0.x);

  return EP >= 0;  
}

bool insideTriangle(const vec2& p, const vec3& v0, const vec3& v1, const vec3& v2) {
  bool inside = true;

  inside &= edgeFunction(p, v0, v1);
  inside &= edgeFunction(p, v1, v2);
  inside &= edgeFunction(p, v2, v0);

  return inside;
}

vec3 getBarycentricCoords(const vec2& p, const vec3& v0, const vec3& v1, const vec3& v2) {
  vec2 p0{v0.x, v1.y}, p1{v1.x, v1.y}, p2{v2.x, v2.y};

  float totalArea = getTriangleArea(p0, p1, p2);

  float b0 = getTriangleArea(p, p1, p2) / totalArea;
  float b1 = getTriangleArea(p, p0, p2) / totalArea;
  float b2 = getTriangleArea(p, p1, p2) / totalArea;

  assert(b0 + b1 + b2 == 1);

  return vec3{b0, b1, b2};
}

float getTriangleArea(const vec2& v0, const vec2& v1, const vec2& v2) {
  // https://ncalculators.com/geometry/triangle-area-by-3-points.htm
  return (1/2) * (v0.x * (v1.y - v2.y) + v1.x * (v2.y - v0.y) + v2.x * (v0.y - v1.y));
}

void interpolate(vec3 bCoords, VertexArrayObject **) {

}

void interpolate(vec3 bCoords, VertexBufferObject *vbo) {

}
