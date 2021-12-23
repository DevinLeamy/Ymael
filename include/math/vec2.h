#ifndef __VEC2__
#define __VEC2__

#include <iostream>

class vec2 {
public:
  float x, y;

  vec2(float x = 0, float y = 0);

  vec2(const vec2& other);
  vec2(vec2&& other);

  vec2 &operator=(const vec2& other);
  float& operator[](int index);

  friend std::ostream& operator<<(std::ostream& os, const vec2& vec); 
  
  ~vec2() = default;

  vec2 &normalize();
  vec2 &scale(float s);

  float length() const;

  static vec2 add(const vec2& left, const vec2& right);
  static vec2 sub(const vec2& left, const vec2& right);
  static vec2 lerp(const vec2& start, const vec2& end, float t);

  static float dot(const vec2& left, const vec2& right);
  static float angle(const vec2& left, const vec2& right);
  static float dist(const vec2& left, const vec2& right);

  static vec2 getNormalized(const vec2 &v);


  vec2 &operator+=(const vec2& right);
  vec2 &operator-=(const vec2& right);

  vec2 operator+(const vec2& right) const;
  vec2 operator-(const vec2& right) const;

  vec2 operator*(float s) const;
};

#endif
