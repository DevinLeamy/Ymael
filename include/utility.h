#include <iostream>
#include <algorithm>

// #ifdef DEBUG_MODE
  // #define PRINTLN(x) std::cout << x << std::endl
  // #define PRINT(x) std::cout << x
  // #define DEBUG(x) std::cout << "DEBUG: " << x << std::endl
// #else
  #define PRINTLN(x) ;
  #define PRINT(x) ; 
  #define DEBUG(x) ;
// #endif

#define TYPE_NAME(T) std::string(typeid(T).name())

#define PI 3.1415926

#define TO_RADIAN(deg) (deg * PI) / 180.0
