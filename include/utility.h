#include <iostream>
#include <algorithm>

#define PRINTLN(x) std::cout << x << std::endl; 

#define DEBUG(x) if (true) std::cout << "DEBUG: " << x << std::endl;

template<typename T>
T clamp(T x, T low, T high) {
  return std::min(high, std::max(x, low));
}
