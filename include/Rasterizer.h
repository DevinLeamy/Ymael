#pragma once

#include "GTriangle.h"
#include "Fragment.h"

class Rasterizer {
public:
  Rasterizer();
  ~Rasterizer() = default;

  // TODO: should be moved elsewhere
  void divideByW();
  void viewportTransform();

  std::vector<std::unique_ptr<Fragment>> rasterize(GTriangle* triangle) const;
};
