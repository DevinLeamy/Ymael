#include <cmath> 

#include "Camera.h"
#include "math/math.h"
#include "utility.h"


Camera::Camera() {
  pos = vec3(0, 0, 0);
  forward = vec3(0, 0, 1);
  up = vec3(0, 1, 0);

  init();
}

Camera::Camera(const vec3& pos, const vec3& forward, const vec3& up): 
  pos{pos}, forward{forward}, up{up} 
{
  init();
}

void Camera::init() {
  forward.normalize();
  up.normalize();
}

vec3 Camera::getPos() const { return pos; }
vec3 Camera::getForward() const { return forward; }
vec3 Camera::getUp() const { return up; }

mat4 Camera::viewMatrix() const {
  vec3 right = vec3::cross(forward, up).scale(-1);

  return mat4({
    {right.x,   right.y,   right.z,   -pos.x},
    {up.x,      up.y,      up.z,      -pos.y},
    {forward.x, forward.y, forward.z, -pos.z},
    {0,         0,         0,         0},
  });
}

mat4 Camera::projectionMatrix(float fov, float ar, float nearZ, float farZ) {
  float tanHFOV = tanf(TO_RADIAN(fov * 0.5));
  float distFN = farZ - nearZ;

  return mat4({
    {1.0f / (tanHFOV * ar), 0,          0,                                                     0},
    {0,                  1.0f / tanHFOV, 0,                                                    0},
    {0,                  0,             (-farZ - nearZ) / distFN, (2 * farZ * nearZ) / distFN, 0},
    {0,                  0,             1,                                                     0}
  });
}


