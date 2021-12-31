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

mat4& mat4::operator=(const mat4& other) {
  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      m[i][j] = other.m[i][j];
  
  return *this;
}

mat4& mat4::operator=(mat4&& other) {
  std::swap(m, other.m);

  return *this;
}

mat4::mat4() {
  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      m[i][j] = 0.0; 
}

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
      res[i] += m[i][j] * right[j];
  
  return res;
}

mat4 mat4::operator*(const mat4 &right) const {
  mat4 res;

  for (size_t i = 0; i < 4; ++i) 
    for (size_t j = 0; j < 4; ++j)
      for (size_t k = 0; k < 4; ++k)
        res.m[i][j] += m[i][k] * right.m[k][j];
  
  return res;
}

mat4& mat4::transpose() {
  mat4 res;

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      res.m[i][j] = m[j][i];
  
  *this = res;

  return *this; 
}

mat4& mat4::invert() {
  // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
  float A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
  float A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
  float A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
  float A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
  float A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
  float A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
  float A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
  float A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
  float A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
  float A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
  float A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
  float A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
  float A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
  float A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
  float A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
  float A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
  float A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
  float A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

  float det = m[0][0] * ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 )
            - m[0][1] * ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 )
            + m[0][2] * ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 )
            - m[0][3] * ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 );
  det = 1 / det;

  mat4 res; 

  res.m[0][0] = det *   ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 );
  res.m[0][1] = det * - ( m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223 );
  res.m[0][2] = det *   ( m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213 );
  res.m[0][3] = det * - ( m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212 );
  res.m[1][0] = det * - ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 );
  res.m[1][1] = det *   ( m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223 );
  res.m[1][2] = det * - ( m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213 );
  res.m[1][3] = det *   ( m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212 );
  res.m[2][0] = det *   ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 );
  res.m[2][1] = det * - ( m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123 );
  res.m[2][2] = det *   ( m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113 );
  res.m[2][3] = det * - ( m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112 );
  res.m[3][0] = det * - ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 );
  res.m[3][1] = det *   ( m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123 );
  res.m[3][2] = det * - ( m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113 );
  res.m[3][3] = det *   ( m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112 );

  *this = res;

  return *this;
}

// scaling matrix
mat4 mat4::scaleM(float x, float y, float z) {
  return mat4({
    {x, 0, 0, 0},
    {0, y, 0, 0},
    {0, 0, z, 0},
    {0, 0, 0, 1}
 });
}

// translation matrix
mat4 mat4::translationM(float x, float y, float z) {
  return mat4({
    {1, 0, 0, x},
    {0, 1, 0, y},
    {0, 0, 1, z},
    {0, 0, 0, 1}
  });
}

// identity matrix
mat4 mat4::identityM() {
  return mat4({
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  });
}
