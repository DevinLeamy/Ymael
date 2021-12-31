#include <algorithm>
#include <cmath>

#include "Rasterizer.h"
#include "VertexArrayObject.h"
#include "math/math.h"
#include "OpenGL.h"
#include "utility.h"
#include "Triangle.h"
#include "BoundingBox.h"

Rasterizer::Rasterizer() {}

void Rasterizer::rasterize(size_t vertices) {
  assert(vertices % 3 == 0);

  // TODO: should be moved elsewhere
  divideByW();
  viewportTransform();

  size_t triangles = vertices / 3;

  PRINT(*vsOutBuffers << *fsInBuffers);

  for (int i = 0; i < triangles; ++i) 
    rasterizeTriangle(i * 3); // i * 3 (index of the 1st vertex)
};

// prospective division
void Rasterizer::divideByW() {
  VertexBufferObject *positions = vsOutBuffers->getAttributeBuffer(0);

  vec4 glPos;
  for (size_t i = 0; i < positions->getSize(); ++i) {
    positions->get(i, glPos);

    float w = glPos.w;
    if (w != 0.0f) {
      glPos.x /= w;
      glPos.y /= w;
      glPos.z /= w;

      positions->set(i, glPos);
    }
  }
}

// [-1, 1] -> [0, WW/WH]
void Rasterizer::viewportTransform() {
  VertexBufferObject *positions = vsOutBuffers->getAttributeBuffer(0);

  vec4 glPos;
  for (size_t i = 0; i < positions->getSize(); ++i) {
    positions->get(i, glPos);
    // assert(glPos.x >= -1 && glPos.x <= 1);
    // assert(glPos.y >= -1 && glPos.y <= 1);

    PRINT(glPos);

    glPos.x = ((glPos.x + 1.0f) * CONST::WW) / 2.0f;
    glPos.y = ((glPos.y + 1.0f) * CONST::WH) / 2.0f;
    
    PRINTLN(glPos);

    positions->set(i, glPos);
  }
}

void Rasterizer::rasterizeTriangle(size_t v0Index) {
  Triangle triangle = getTriangle(v0Index);

  if (triangle.area() == 0.0f) return;

  BoundingBox windowBBox{
    .minX = 0, .maxX = CONST::WW,
    .minY = 0, .maxY = CONST::WH
  };
  
  std::vector<vec2> coveredPoints = Triangle::getCoveredPoints(triangle, windowBBox);
  fragmentCount += coveredPoints.size();

  for (const vec2& point : coveredPoints) {
    assert(point.x >= 0 && point.x <= CONST::WW);
    assert(point.y >= 0 && point.y <= CONST::WH);
    for (int attrIndex : vsOutBuffers->getEnabledAttributes()) {
      // position 
      if (attrIndex == 0) {
        VertexBufferObject* inVBO = vsOutBuffers->getAttributeBuffer(attrIndex);
        VertexBufferObject* outVBO = fsInBuffers->getAttributeBuffer(attrIndex);


        vec4 p0, p1, p2;

        inVBO->get(v0Index, p0);
        inVBO->get(v0Index, p1);
        inVBO->get(v0Index, p2);

        vec3 vals(p0.z, p1.z, p2.z);

        float interpolatedZ = triangle.interpolateFloat(vals, point);

        vec4 newPos(point.x, point.y, interpolatedZ, 1.0);

        outVBO->bind(newPos);
      } else {
        interpolateAttribute(v0Index, attrIndex, point, triangle);
      }
    }
  }
}

Triangle Rasterizer::getTriangle(size_t v0Index) const {
  vec4 v0, v1, v2;

  vsOutBuffers->getAttributeBuffer(0)->get(v0Index + 0, v0);
  vsOutBuffers->getAttributeBuffer(0)->get(v0Index + 1, v1);
  vsOutBuffers->getAttributeBuffer(0)->get(v0Index + 2, v2);

  return Triangle(vec2(v0.x, v0.y), vec2(v1.x, v1.y), vec2(v2.x, v2.y));
}

void Rasterizer::interpolateAttribute(size_t v0Index, size_t attrIndex, const vec2& point, const Triangle& triangle) {
  VertexBufferObject *inBuffer = vsOutBuffers->getAttributeBuffer(attrIndex);
  VertexBufferObject *outBuffer = fsInBuffers->getAttributeBuffer(attrIndex);

  size_t attributeSize = inBuffer->getItemSize();

  for (size_t i = 0; i < attributeSize; ++i) {
    vec3 floats;
    floats.x = inBuffer->getRawFloat(attributeSize * (v0Index + 0) + i);
    floats.y = inBuffer->getRawFloat(attributeSize * (v0Index + 1) + i);
    floats.z = inBuffer->getRawFloat(attributeSize * (v0Index + 2) + i);

    float interpolated = triangle.interpolateFloat(floats, point);

    outBuffer->bind(interpolated);
  }

}
