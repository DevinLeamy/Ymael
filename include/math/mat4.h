#pragma once

#include <vector>

#include "math/vec4.h"

class mat4 {
  public:
    float m[4][4];

    mat4(std::vector<std::vector<float>> m); 

    vec4 operator*(const vec4 &right) const; 

    static mat4 scale(float x, float y, float z);
    static mat4 translate(float x, float y, float z);
    static mat4 identity();
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
