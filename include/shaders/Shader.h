#pragma once

#include <memory>
#include <vector>
#include <map>

#include "GraphicsObject.h"

class Shader {
public:
  Shader() = default;
  virtual ~Shader() = default;
  virtual void run(GraphicsObject* inGO, GraphicsObject* outGO) = 0;
};
