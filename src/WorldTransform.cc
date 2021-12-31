#pragma once

#include "WorldTransform.h"
#include "math/math.h"

WorldTransform::WorldTransform() {
  m_translation = vec3(0.0f, 0.0f, 0.0f);
  m_rotation = vec3(0.0f, 0.0f, 0.0f);
  m_scale = 1.0f;
}

WorldTransform::WorldTransform(const vec3& translation, const vec3& rotation, float scale):
  m_translation{translation}, m_rotation{rotation}, m_scale{scale} {}

void WorldTransform::rotate(const vec3& rotation) {
  m_rotation = m_rotation + rotation;
}

void WorldTransform::translate(const vec3& translation) {
  m_translation = m_translation + translation;
}

void WorldTransform::scale(float scale) {
  m_scale *= scale;
}

mat4 WorldTransform::toMatrix() const {
  mat4 T = mat4::translationM(m_translation.x, m_translation.y, m_translation.z);
  mat4 S = mat4::scaleM(m_scale, m_scale, m_scale);
  mat4 R = quat::rotationQuat(m_rotation.x, m_rotation.y, m_rotation.z).toMatrix();

  return T * R * S;
}
