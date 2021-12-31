#pragma once

#include "math/math.h"


class WorldTransform {
public:
  WorldTransform();
  WorldTransform(const vec3& translation, const vec3& rotation, float scale);

  inline const vec3& getTranslation() const { return m_translation; }
  inline const vec3& getRotation() const { return m_rotation; }
  inline float getScale() const { return m_scale; }

  void rotate(const vec3& rotationD); 
  void translate(const vec3& translationD);
  void scale(float scaleD);

  mat4 toMatrix() const;

private:
  vec3 m_translation;
  vec3 m_rotation;
  float m_scale = 1.0f;
};
