#pragma once

#include "GraphicsObject.h"

class Vertex: public GraphicsObject {
public:
  Vertex();
  Vertex(const std::map<int, Attribute*>& attrMap);

  vec4 getPosition() const;

  ~Vertex() = default;
};
