#include "shaders/VertexShader.h"
#include "math/math.h"

class BasicVertexShader: public VertexShader {
public:
  BasicVertexShader(): VertexShader {} {}

  void run(VertexArrayObject *inStream, VertexArrayObject *outStream, std::vector<int> attrIndices) override {
    // assumes ATTRIBUTE VBOs: { positions, uvs, normals }
    vec3 pos;
    vec2 uv;
    vec3 normals;

    inStream->getAttributeBuffer<vec3>(0)->get(attrIndices[0], pos);
    inStream->getAttributeBuffer<vec2>(1)->get(attrIndices[1], uv);
    inStream->getAttributeBuffer<vec3>(2)->get(attrIndices[2], normals);

    // some manipulation

    // store a position
    outStream->getAttributeBuffer<vec3>(0)->bind(pos);
  }

  void run(VertexArrayObject* inStream, VertexArrayObject* outStream, int vertexIndex) override {
    
  }
};
