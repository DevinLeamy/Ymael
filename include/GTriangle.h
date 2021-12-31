#pragma once

#include "Vertex.h"
#include "Triangle.h"
#include "Fragment.h"
#include "math/math.h"

class GTriangle: public Triangle {
public:
  GTriangle(Vertex* a, Vertex* b, Vertex* c);

  void interpolate(const vec2& point, Fragment *fragment) const; 

  ~GTriangle() = default;
private:
  std::vector<float> interpolateAttribute(const vec2& point, int attrIndex) const; 

  Vertex* p_a;
  Vertex* p_b;
  Vertex* p_c;

  std::vector<int> attributes;
};
