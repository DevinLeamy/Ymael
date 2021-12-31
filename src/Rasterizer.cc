#include <algorithm>
#include <cmath>

#include "Rasterizer.h"
#include "math/math.h"
#include "OpenGL.h"
#include "utility.h"
#include "GTriangle.h"
#include "BoundingBox.h"

Rasterizer::Rasterizer() {}

std::vector<std::unique_ptr<Fragment>> Rasterizer::rasterize(GTriangle* triangle) const {
  if (triangle->area() == 0.0f) return {};

  std::vector<std::unique_ptr<Fragment>> fragments;

  BoundingBox windowBBox{
    .minX = 0, .maxX = CONST::WW,
    .minY = 0, .maxY = CONST::WH
  };

  std::vector<vec2> coveredPoints = Triangle::getCoveredPoints(triangle, windowBBox);

  for (const vec2& point : coveredPoints) {
    assert(point.x >= 0 && point.x <= CONST::WW);
    assert(point.y >= 0 && point.y <= CONST::WH);

    std::unique_ptr<Fragment> fragment = std::make_unique<Fragment>();

    triangle->interpolate(point, fragment.get());

    fragments.push_back(std::move(fragment));
  }

  return std::move(fragments);
}

// // perspective division
// void Rasterizer::divideByW() {
//   VertexBufferObject *positions = vsOutBuffers->getAttributeBuffer(0);

//   vec4 glPos;
//   for (size_t i = 0; i < positions->getSize(); ++i) {
//     positions->get(i, glPos);

//     float w = glPos.w;
//     if (w != 0.0f) {
//       glPos.x /= w;
//       glPos.y /= w;
//       glPos.z /= w;

//       positions->set(i, glPos);
//     }
//   }
// }

// // [-1, 1] -> [0, WW/WH]
// void Rasterizer::viewportTransform() {
//   VertexBufferObject *positions = vsOutBuffers->getAttributeBuffer(0);

//   vec4 glPos;
//   for (size_t i = 0; i < positions->getSize(); ++i) {
//     positions->get(i, glPos);
//     // assert(glPos.x >= -1 && glPos.x <= 1);
//     // assert(glPos.y >= -1 && glPos.y <= 1);

//     PRINT(glPos);

//     glPos.x = ((glPos.x + 1.0f) * CONST::WW) / 2.0f;
//     glPos.y = ((glPos.y + 1.0f) * CONST::WH) / 2.0f;
    
//     PRINTLN(glPos);

//     positions->set(i, glPos);
//   }
// }
