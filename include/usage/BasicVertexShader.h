#include "shaders/VertexShader.h"
#include "math/math.h"
#include "utility.h"

class BasicVertexShader: public VertexShader {
public:
  BasicVertexShader(): VertexShader {} {
    inputBufferMap[0] = 3; // position
    inputBufferMap[1] = 2; // uvs
    inputBufferMap[2] = 3; // normals
    inputBufferMap[3] = 3; // colours

    outputBufferMap[0] = 3; // position
    outputBufferMap[1] = 1; // uvs 
  }

  ~BasicVertexShader() = default;

  void run(VertexArrayObject *inStream, VertexArrayObject *outStream, std::vector<int> attrIndices) override {
    vec3 pos; // in
    vec2 uv;  // in/out
    vec3 normals; // in

    vec3 screenSpacePos; // out

    DEBUG("SET VERTEX SHADER INPUTS");
    inStream->getAttributeBuffer(0)->get(attrIndices[0], pos);
    inStream->getAttributeBuffer(1)->get(attrIndices[1], uv);
    inStream->getAttributeBuffer(2)->get(attrIndices[2], normals);


    // some manipulation

    // store a position
    DEBUG("SET VERTEX SHADER OUTPUTS");
    outStream->getAttributeBuffer(0)->bind(screenSpacePos);
    outStream->getAttributeBuffer(1)->bind(uv);
  }
};
