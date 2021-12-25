#pragma once

#include <vector>
#include <cassert>

#include "math/vec4.h"
#include "math/mat4.h"

/*
Points and vectors are both represented as mathematical column 
vectors (column-matrix representation scheme, see note below) in 
homogeneous coordinates with the difference that points have a 1 
in the fourth position whereas vectors have a zero at this position, 
which removes translation operations (4th column) for vectors.


Affine transformation matrix:
Top left 3x3 - transformations
Far right 3x1 - transformations
Bottom row - (0, 0, 0, 1)
*/


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

// scaling matrix
mat4 mat4::scaleMat(float x, float y, float z) {
  return mat4({
    {x, 0, 0, 0},
    {0, y, 0, 0},
    {0, 0, z, 0},
    {0, 0, 0, 1}
  })
}

// translation matrix
mat4 translationMat(float x, float y, float z) {
  return mat4({
    {1, 0, 0, x},
    {0, 1, 0, y},
    {0, 0, 1, z},
    {0, 0, 0, 1}
  });
}

// identity matrix
mat4 identityMat() {
  return mat4({
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  });
}
