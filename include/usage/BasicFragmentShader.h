#include "shaders/FragmentShader.h"
#include "math/math.h"

class BasicFragmentShader: public FragmentShader {
public:
  BasicFragmentShader(): FragmentShader {} {
    inputBufferMap[0] = 3; // position
    inputBufferMap[1] = 2; // uvs

    outputBufferMap[0] = 3; // colour
  }

  ~BasicFragmentShader() = default;

  void run(VertexArrayObject *inStream, VertexArrayObject *outStream, std::vector<int> attrIndices) override {
    vec3 pos; // in
    vec2 uvs; // in

    vec3 colour; // out

    inStream->getAttributeBuffer(0)->get(attrIndices[0], pos);
    inStream->getAttributeBuffer(1)->get(attrIndices[1], uvs);

    colour = vec3{255, 255, 255};

    outStream->getAttributeBuffer(0)->bind(colour);
  }
};
