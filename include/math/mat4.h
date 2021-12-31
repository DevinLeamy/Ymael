#pragma once

#include <vector>

#include "math/vec4.h"

class mat4 {
  public:
    float m[4][4];

    mat4();
    mat4(std::vector<std::vector<float>> m); 
    mat4(const mat4 &m);
    mat4(mat4 &&m);

    mat4& operator=(const mat4& other);
    mat4& operator=(mat4&& other);

    vec4 operator*(const vec4 &right) const; 
    mat4 operator*(const mat4 &right) const;

    mat4& transpose();
    mat4& invert();

    static mat4 scaleM(float x, float y, float z);
    static mat4 translationM(float x, float y, float z);
    static mat4 identityM();

    ~mat4() = default;
};
