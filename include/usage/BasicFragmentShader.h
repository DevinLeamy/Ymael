#include "shaders/FragmentShader.h"
#include "math/math.h"

class BasicFragmentShader: public FragmentShader {
public:
  BasicFragmentShader(): FragmentShader {} {}

  void run(VertexArrayObject *inStream, VertexArrayObject *outStream, std::vector<int> attrIndices) override {
    // assumes ATTRIBUTE VBOs: { positions, uvs, normals }
    vec3 colour;

    inStream->getAttributeBuffer(0)->get(attrIndices[0], colour);

    outStream->getAttributeBuffer(0)->bind(colour);
  }

  void run(VertexArrayObject* inStream, VertexArrayObject* outStream, int vertexIndex) override {
    
  }
};
