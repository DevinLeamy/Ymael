#include <string>

#include "shaders/FragmentShader.h"
#include "math/math.h"

class BasicFragmentShader: public FragmentShader {
public:
  BasicFragmentShader(): FragmentShader {} {
    inputBufferMap[0] = 4; // pos 
    inputBufferMap[1] = 2; // uvs

    outputBufferMap[0] = 3; // screenCoord
    outputBufferMap[1] = 3; // colour 
  }

  ~BasicFragmentShader() = default;

  void run(VertexArrayObject *inStream, VertexArrayObject *outStream, std::vector<int> attrIndices) override {
    std::string shades = ".o*";

    vec4 pos; // in
    vec2 uvs; // in

    vec3 screenCoord; // out
    vec3 colour; // out

    inStream->getAttributeBuffer(0)->get(attrIndices[0], pos);
    inStream->getAttributeBuffer(1)->get(attrIndices[1], uvs);

    screenCoord = vec3(pos.x, pos.y, pos.z);
    colour = vec3(std::min(1.0f, uvs.length()) * 8.0f, 100, 100);

    outStream->getAttributeBuffer(0)->bind(screenCoord);
    outStream->getAttributeBuffer(1)->bind(colour);
  }
};
