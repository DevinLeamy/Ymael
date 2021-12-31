#pragma once

/*
UVN camera model
*/

#include "math/math.h"
#include <vector>

class Camera {
public:

  Camera();
  Camera(const vec3& pos, const vec3& forward, const vec3& up); 

  ~Camera() = default;

  void init();

  mat4 viewMatrix() const;
  vec3 getPos() const;
  vec3 getForward() const;
  vec3 getUp() const;

  // fov = field of view, ar = aspect ratio
  static mat4 projectionMatrix(float fov, float ar, float nearZ, float farZ); 

private:
  vec3 pos;
  vec3 forward; // defaults to positive z axis 
  vec3 up; // default to y axis
};
