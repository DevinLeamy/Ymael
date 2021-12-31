#pragma once

#include "GraphicsObject.h"

class Fragment: public GraphicsObject {
public:
  Fragment();
  Fragment(const std::map<int, Attribute*>& attrMap);

  vec3 getPosition() const;
  vec3 getColor() const;

  ~Fragment() = default;
};
