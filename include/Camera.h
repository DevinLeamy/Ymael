#pragma once

#include <vector>
#include <iostream>
/*
UVN camera model
*/

#include "math/math.h"

class Camera {
public:

  Camera();
  Camera(const vec3& pos, const vec3& forward, const vec3& up); 

  ~Camera() = default;

  void init();

  mat4 viewMatrix() const;
  vec3 getPos() const;
  vec3 getForward() const;
  vec3 getUp() const;

  void update_temp(char key) {
    float STEP_SCALE = 5.0f;
    switch (key) {
    case 'w': {
      // std::cout << pos << std::endl;
      pos += up * STEP_SCALE;
      // std::cout << pos << std::endl;
    }
    break;
    case 's': {
      pos -= up * STEP_SCALE;
    }
    break;
    case 'f': {
      pos += forward * STEP_SCALE; 
    }
    break;
    case 'b': {
      pos -= forward * STEP_SCALE;
    }
    break;
    case 'a': {
      vec3 left = vec3::cross(forward, up).normalize();
      left = left * STEP_SCALE;
      pos += left;
    }
    break;

    case 'd': {
      vec3 right = vec3::cross(up, forward).normalize(); 
      right = right * STEP_SCALE;
      pos += right;
    }
    break;
    default:
      break;            
    }
  }



  // fov = field of view, ar = aspect ratio
  static mat4 projectionMatrix(float fov, float ar, float nearZ, float farZ); 

private:
  vec3 pos;
  vec3 forward; // defaults to positive z axis 
  vec3 up; // default to y axis
};
