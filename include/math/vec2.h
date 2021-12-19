#ifndef __VEC2__
#define __VEC2__

#include <iostream>

class vec2 {
public:
  double x, y;

  vec2(double x = 0, double y = 0);

  vec2(const vec2& other);
  vec2(vec2&& other);

  vec2 &operator=(const vec2& other);

  friend std::ostream& operator<<(std::ostream& os, const vec2& vec); 
  
  ~vec2() = default;

  vec2 &normalize();
  vec2 &scale(double s);

  double length() const;

  static vec2 add(const vec2& left, const vec2& right);
  static vec2 sub(const vec2& left, const vec2& right);
  static vec2 lerp(const vec2& start, const vec2& end, double t);

  static double dot(const vec2& left, const vec2& right);
  static double angle(const vec2& left, const vec2& right);
  static double dist(const vec2& left, const vec2& right);

  static vec2 getNormalized(const vec2 &v);


  vec2 &operator+=(const vec2& right);
  vec2 &operator-=(const vec2& right);

  vec2 operator+(const vec2& right) const;
  vec2 operator-(const vec2& right) const;

  vec2 operator*(double s) const;
};

#endif
