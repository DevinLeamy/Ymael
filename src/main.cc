#include <iostream>

#include "math/vec2.h"

int main() {
  vec2 v1(3, 3);
  vec2 v2(2, 7);

  std::cout << v1 << v1 + v2 << vec2::dot(v1, v2) << " " << vec2::angle(v1, v2) << std::endl;
  std::cout << vec2::getNormalized(v1).length() << v1.normalize() << v1 * 5;
}
