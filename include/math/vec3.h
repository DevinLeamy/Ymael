#ifndef __VEC3__
#define __VEC3__

#include <iostream>

class vec3 {
public:
  double x, y, z;

  vec3(double x = 0, double y = 0, double z = 0);

  vec3(const vec3& other);

  vec3 &operator=(const vec3& other);

  friend std::ostream& operator<<(std::ostream& os, const vec3& vec); 
  
  ~vec3() = default;

  // create vector of magnitude 1 
  vec3 &normalize();
  vec3 &scale(double s);

  // magnitude
  double length() const;

  static vec3 add(const vec3& left, const vec3& right);
  static vec3 sub(const vec3& left, const vec3& right);

  // cross product: vector orthogonal to left and right
  static vec3 cross(const vec3& left, const vec3& right);

  // linear interpolation 
  static vec3 lerp(const vec3& start, const vec3& end, double t);

  // dot product: "similarily" of two vectors
  static double dot(const vec3& left, const vec3& right);

  // angle between two vectors
  static double angle(const vec3& left, const vec3& right);

  // distance between two vector end points
  static double dist(const vec3& left, const vec3& right);

  static vec3 getNormalized(const vec3 &v);


  vec3 &operator+=(const vec3& right);
  vec3 &operator-=(const vec3& right);

  vec3 operator+(const vec3& right) const;
  vec3 operator-(const vec3& right) const;

  vec3 operator*(double s) const;
};

#endif
