#pragma once

#include <vector>
#include <cassert>

#include "math/vec4.h"
#include "math/mat4.h"


mat4::mat4(std::vector<std::vector<float>> m) {
  assert(m.size() == 4 && m[0].size() == 4);

  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      this->m[i][j] = m[i][j];
}

vec4 mat4::operator*(const vec4 &right) const {
  vec4 res;

  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      res[i] = m[i][j] * right[j];
  
  return res;
}

mat4 mat4::scaleMat(float x, float y, float z) {

}

mat4 translationMat(float x, float y, float z) {
  return mat4({
    {1, 0, 0, x},
    {0, 1, 0, y},
    {0, 0, 1, z},
    {0, 0, 0, 1}
  });
}

mat4 identityMat() {
  return mat4({
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  });
}

/*
Translation matrices:
[
 [1, 0, 0, X],
 [0, 1, 0, Y],
 [0, 0, 1, Z],
 [0, 0, 0, 1]
]
- Adds X, Y, Z to your position



Cumulating transformations:
TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
*/
