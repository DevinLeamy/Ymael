#pragma once

#include "math/math.h"

class quat {
public:
  quat(float x = 0, float y = 0, float z = 0, float w = 1);
  static quat rotationQuat(float xAngle, float yAngle, float zAngle);

  mat4 toMatrix() const;
  // q = w + xi + yj + zk
  float x, y, z, w;
};
