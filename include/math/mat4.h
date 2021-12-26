#pragma once

#include <vector>

#include "math/vec4.h"

class mat4 {
  public:
    float m[4][4];

    mat4(std::vector<std::vector<float>> m); 
    mat4(const mat4 &m);
    mat4(mat4 &&m);

    mat4& operator=(const mat4& other);
    mat4& operator=(mat4&& other);

    vec4 operator*(const vec4 &right) const; 

    // const std::vector<float> &toVector() const;

    static mat4 scaleM(float x, float y, float z);
    static mat4 translationM(float x, float y, float z);
    static mat4 identityM();

    ~mat4() = default;
};

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
