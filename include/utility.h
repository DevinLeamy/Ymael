#include <iostream>
#include <algorithm>

#define PRINTLN(x) std::cout << x << std::endl; 
#define DEBUG(x) if (true) std::cout << "DEBUG: " << x << std::endl;

#define TYPE_NAME(T) std::string(typeid(T).name())

template<typename T>
T clamp(T x, T low, T high) {
  return std::min(high, std::max(x, low));
}
