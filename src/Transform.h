#pragma once

#include "math/math.h"


struct Transform {
  vec3 position;
  vec3 rotation;
  vec3 scale;
};

mat4 createTransformMat(Transform transform) {
  vec3 pos = transform.position;
  vec3 rot = transform.rotation;
  vec3 scale = transform.scale;

  mat4 T = mat4::translationM(pos.x, pos.y, pos.z);
  mat4 S = mat4::scaleM(scale.x, scale.y, scale.z);
  mat4 R = quat::rotationQuat(rot.x, rot.y, rot.z).toMatrix();

  return T * R * S;
}

