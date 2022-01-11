#include <string>
#include <cmath>

#include "shaders/FragmentShader.h"
#include "math/math.h"

class BasicFragmentShader: public FragmentShader {
public:
  BasicFragmentShader(): FragmentShader {} {
    // TODO: remove? 
    inputBufferMap[0] = 4; // pos 
    inputBufferMap[1] = 2; // uvs

    outputBufferMap[0] = 3; // screenCoord
    outputBufferMap[1] = 3; // colour 
  }

  ~BasicFragmentShader() = default;

  void run(GraphicsObject* fragmentIn, GraphicsObject* fragmentOut) {
    std::string shades = ".o*";

    // in
    vec4 pos; 
    vec2 uvs; 

    // out
    vec3 screenCoord; 
    vec3 colour; 

    fragmentIn->get(0, pos);
    fragmentIn->get(1, uvs);

    screenCoord = vec3(pos.x, pos.y, pos.z);
    colour = vec3((int) (uvs.x * 8.0f) % 8, 100, 100);

    fragmentOut->set(0, screenCoord);
    fragmentOut->set(1, colour);
  }
};
