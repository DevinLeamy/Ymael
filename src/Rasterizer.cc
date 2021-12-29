#include <algorithm>
#include <cmath>

#include "Rasterizer.h"
#include "VertexArrayObject.h"
#include "math/math.h"
#include "OpenGL.h"
#include "utility.h"

size_t interpolate(VertexArrayObject*, VertexArrayObject*, int);
std::vector<vec2> getCoveredPixels(const vec4&, const vec4&, const vec4&);
bool edgeFunction(const vec4&, const vec4&, const vec4&);
bool insideTriangle(const vec2&, const vec4&, const vec4&, const vec4&);
bool isLeftOrTopEdge(const vec4&, const vec4&, const vec4&);
vec3 getBarycentricCoords(const vec2&, const vec4&, const vec4&, const vec4&);
float getTriangleArea(const vec2&, const vec2&, const vec2&);

int Rasterizer::rasterize(VertexArrayObject *vVAO, VertexArrayObject *fVAO, int vertices) {
  assert(vertices % 3 == 0);

  int fragments = 0;

  for (int i = 0; i < vertices; i += 3) {
    // DEBUG("RASTERIZE TRIANGLE");
    fragments += interpolate(vVAO, fVAO, i);
  }

  return fragments;
};

// vIndex == index of the first vertex
size_t interpolate(VertexArrayObject *vVAO, VertexArrayObject *fVAO, int vIndex) {
  // vertices of the triangle are [vIndex, vIndex + 1, vIndex + 2]
  // assumes position is the first attribute
  vec4 v0, v1, v2;

  vVAO->getAttributeBuffer(0)->get(vIndex, v0);
  vVAO->getAttributeBuffer(0)->get(vIndex + 1, v1);
  vVAO->getAttributeBuffer(0)->get(vIndex + 2, v2);

  PRINT(v0 << v1 << v2);

  std::vector<vec2> coveredPixels = getCoveredPixels(v0, v1, v2);

  std::vector<int> attrIndices = vVAO->getEnabledAttributes();

  for (vec2 pixel : coveredPixels) {
    vec3 bCoords;
    try {
      bCoords = getBarycentricCoords(pixel, v0, v1, v2);
    } catch (...) { continue; }

    for (int attrIndex : attrIndices) {
      VertexBufferObject* inVBO = vVAO->getAttributeBuffer(attrIndex);
      VertexBufferObject* outVBO = fVAO->getAttributeBuffer(attrIndex);

      // position 
      if (attrIndex == 0) {
        vec4 p0, p1, p2;

        inVBO->get(vIndex, p0);
        inVBO->get(vIndex, p1);
        inVBO->get(vIndex, p2);

        float interpolatedZ = bCoords.x * p0.z + bCoords.y * p1.z + bCoords.z * p2.z;

        vec4 newPos(pixel.x, pixel.y, interpolatedZ, 1.0);

        outVBO->bind(newPos);
        continue;
      }

      size_t itemSize = inVBO->getItemSize();

      for (size_t i = 0; i < itemSize; ++i) {
        float f0 = inVBO->getRawFloat(itemSize * (vIndex + 0) + i);
        float f1 = inVBO->getRawFloat(itemSize * (vIndex + 1) + i);
        float f2 = inVBO->getRawFloat(itemSize * (vIndex + 2) + i);

        float interpolated = bCoords.x * f0 + bCoords.y * f1 + bCoords.z * f2;

        outVBO->bind(interpolated);
      }
    }
  }

  for (vec2 pixel : coveredPixels)
    PRINT(pixel);

  return coveredPixels.size();
}

// TODO: optimize
std::vector<vec2> getCoveredPixels(const vec4& p1, const vec4& p2, const vec4& p3) {
  std::vector<vec2> covered;

  // PRINT(p1 << p2 << p3);
  PRINT(p1);

  int minX = std::clamp<int>(std::min({p1.x, p2.x, p3.x}), 0, CONST::WW);
  int maxX = std::clamp<int>(std::max({p1.x, p2.x, p3.x}), 0, CONST::WW);

  int minY = std::clamp<int>(std::min({p1.y, p2.y, p3.y}), 0, CONST::WH);
  int maxY = std::clamp<int>(std::max({p1.y, p2.y, p3.y}), 0, CONST::WH);

  for (int i = minX; i < maxX; ++i) {
    bool wasInside = false;

    for (int j = minY; j < maxY; ++j) {
      vec2 point{i + 0.5f, j + 0.5f};

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
bool edgeFunction(const vec2& p, const vec4& v0, const vec4& v1) {
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
  return (p.x - v0.x) * (v1.y - v0.y) -
         (p.y - v0.y) * (v1.x - v0.x);
}

bool insideTriangle(const vec2& p, const vec4& v0, const vec4& v1, const vec4& v2) {
  bool inside = true;

  float e0 = edgeFunction(p, v0, v1);
  float e1 = edgeFunction(p, v1, v2);
  float e2 = edgeFunction(p, v2, v0);

  inside &= (e0 == 0) ? isLeftOrTopEdge(v0, v1, v2) : e0 > 0;
  inside &= (e1 == 0) ? isLeftOrTopEdge(v1, v2, v0) : e1 > 0;
  inside &= (e2 == 0) ? isLeftOrTopEdge(v2, v0, v1) : e2 > 0;

  return inside;
}

bool isLeftOrTopEdge(const vec4& v0, const vec4& v1, const vec4& other) {
  // top edge test
  if (v0.y == v1.y && other.y > v0.y)
    return true;
  
  // left edge test
  if (v0.y > v1.y)
    return true;
  
  return false;
}

vec3 getBarycentricCoords(const vec2& p, const vec4& v0, const vec4& v1, const vec4& v2) {
  vec2 p0{v0.x, v0.y}, p1{v1.x, v1.y}, p2{v2.x, v2.y};

  float totalArea = getTriangleArea(p0, p1, p2);

  if (totalArea == 0) 
    throw 1;

  float b0 = getTriangleArea(p, p0, p1) / totalArea;
  float b1 = getTriangleArea(p, p1, p2) / totalArea;
  float b2 = getTriangleArea(p, p2, p0) / totalArea;

  assert(b0 >= 0 && b1 >= 0 && b2 >= 0);

  // PRINTLN(b0 + b1 + b2 << " " << totalArea);
  // assert(abs((b0 + b1 + b2) - 1.0f) < 0.01f);

  return vec3{b0, b1, b2};
}

float getTriangleArea(const vec2& v0, const vec2& v1, const vec2& v2) {
  // https://ncalculators.com/geometry/triangle-area-by-3-points.htm
  return abs(v0.x * (v1.y - v2.y) + v1.x * (v2.y - v0.y) + v2.x * (v0.y - v1.y)) * 0.5;
}
