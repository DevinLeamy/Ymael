#include <cmath>

#include "math/quat.h"

quat::quat(float x, float y, float z, float w): x{x}, y{y}, z{z}, w{w} {}

quat quat::rotationQuat(float xAngle, float yAngle, float zAngle) {
  // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
  float cy = cos(zAngle * 0.5);
  float sy = sin(zAngle * 0.5);
  float cp = cos(yAngle * 0.5);
  float sp = sin(yAngle * 0.5);
  float cr = cos(xAngle * 0.5);
  float sr = sin(xAngle * 0.5);

  quat q;
  q.x = sr * cp * cy - cr * sp * sy;
  q.y = cr * sp * cy + sr * cp * sy;
  q.z = cr * cp * sy - sr * sp * cy;
  q.w = cr * cp * cy + sr * sp * sy;

  return q;
}

mat4 quat::toMatrix() const {
  // http://www.songho.ca/opengl/gl_quaternion.html
  return mat4({
    { 1 - 2*y*y - 2*z*z, 2*x*y - 2*w*z,     2*x*z + 2*w*y,     0 },
    { 2*x*y + 2*w*z,     1 - 2*x*x - 2*z*z, 2*y*z - 2*w*x,     0 },
    { 2*x*z - 2*w*y,     2*y*z + 2*w*x,     1 - 2*x*x - 2*y*y, 0 },
    { 0,                 0,                 0,                 1 }
  });
}
