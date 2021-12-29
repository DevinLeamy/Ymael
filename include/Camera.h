#pragma once

/*
UVN camera model
*/

#include "math/math.h"
#include <vector>

class Camera {
public:

  Camera(vec3 pos = vec3(0, 0, 0), vec3 u = vec3(1, 0, 0), vec3 v = vec3(0, 1, 0), vec3 n = vec3(0, 0, 1)); 

  ~Camera() = default;

  mat4 viewMatrix() const;

  // fov = field of view, ar = aspect ratio
  static mat4 projectionMatrix(float fov, float ar, float nearZ, float farZ); 

private:
  vec3 pos;
  vec3 u; // default to x axis
  vec3 v; // default to y axis
  vec3 n; // default to z axis
};
