#include <memory>
#include <cassert>
#include <iostream>

#include "shaders/VertexShader.h"
#include "math/math.h"
#include "utility.h"
#include "GraphicsObject.h"
#include "Vertex.h"

class BasicVertexShader: public VertexShader {
public:
  BasicVertexShader(): VertexShader {} {
    // TODO: delete inputBufferMap and outputBufferMap?
    inputBufferMap[0] = 3; // position
    inputBufferMap[1] = 2; // uvs
    inputBufferMap[2] = 3; // normals
    inputBufferMap[3] = 3; // colours

    outputBufferMap[0] = 4; // position
    outputBufferMap[1] = 2; // uvs 
  }

  ~BasicVertexShader() = default;

  void run(GraphicsObject* inVertex, GraphicsObject* outVertex) override {
    // in
    vec3 pos;
    vec2 uv; 
    vec3 normals; 

    // out
    vec4 glPos; 

    DEBUG("SET VERTEX SHADER INPUTS");
    inVertex->get(0, pos);
    inVertex->get(1, uv);
    inVertex->get(2, normals);

    PRINTLN(pos);

    glPos = projectionMatrix * viewMatrix * modelMatrix * vec4(pos.x, pos.y, pos.z, 1.0);

    PRINTLN(glPos);

    // divide by w
    // glPos.x /= glPos.w;
    // glPos.y /= glPos.w;
    // glPos.z /= glPos.w;

    // viewport transform
    // glPos.x = ((glPos.x + 1.0f) * CONST::WW) / 2.0f;
    // glPos.y = ((glPos.y + 1.0f) * CONST::WH) / 2.0f;

    // std::cout << glPos << std::endl;

    outVertex->set(0, glPos.toVector());
    outVertex->set(1, uv.toVector());
  }
};
