#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>

#include "Rasterizer.h"
#include "math/math.h"
#include "OpenGL.h"
#include "utility.h"
#include "GTriangle.h"
#include "BoundingBox.h"

Rasterizer::Rasterizer() {}

std::vector<std::unique_ptr<Fragment>> Rasterizer::rasterize(GTriangle* triangle) const {
  if (triangle->area() == 0.0f) return {};

  BoundingBox windowBBox{
    .minX = 0, .maxX = CONST::WW,
    .minY = 0, .maxY = CONST::WH
  };

  std::vector<vec2> coveredPoints = Triangle::getCoveredPoints(triangle, windowBBox);
  std::vector<std::unique_ptr<Fragment>> fragments;

  for (const vec2& point : coveredPoints) {
    assert(point.x >= 0 && point.x <= CONST::WW);
    assert(point.y >= 0 && point.y <= CONST::WH);

    std::unique_ptr<Fragment> fragment = std::make_unique<Fragment>();

    triangle->interpolate(point, fragment.get());

    fragments.push_back(std::move(fragment));
  }

  return std::move(fragments);
}
