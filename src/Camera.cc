#include <cmath> 

#include "Camera.h"
#include "math/math.h"
#include "utility.h"


Camera::Camera(vec3 pos, vec3 u, vec3 v, vec3 n): pos{pos}, u{u}, v{v}, n{n} {
  u.normalize();
  v.normalize();
  n.normalize();
}

mat4 Camera::viewMatrix() const {
  return mat4({
    {u.x, u.y, u.z, -pos.x},
    {v.x, v.y, v.z, -pos.y},
    {n.x, n.y, n.z, -pos.z},
    {0,   0,   0,   0},
  });
}

mat4 Camera::projectionMatrix(float fov, float ar, float nearZ, float farZ) {
  float invTanHalfFOV= 1.0f / tan(TO_RADIAN(fov * 0.5));
  float distFN = farZ - nearZ;

  return mat4({
    {invTanHalfFOV * ar, 0,             0,                                                     0},
    {0,                  invTanHalfFOV, 0,                                                     0},
    {0,                  0,             (-farZ - nearZ) / distFN, (2 * farZ * nearZ) / distFN, 0},
    {0,                  0,             1,                                                     0}
  });
}


