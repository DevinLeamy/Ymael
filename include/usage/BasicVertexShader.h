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
    outputBufferMap[2] = 3; // transformed normals
    outputBufferMap[3] = 3; // transformed light position

    // TODO: refactor uniform system to and make this just another uniform
    lightPosition = vec3(0, 0, 50);
  }

  ~BasicVertexShader() = default;

  void run(GraphicsObject* inVertex, GraphicsObject* outVertex) override {
    // in
    vec3 pos;
    vec2 uv; 
    vec3 normal; 

    // out
    vec4 glPos; 
    vec3 tNormal;
    vec3 tLightPos;

    DEBUG("SET VERTEX SHADER INPUTS");
    inVertex->get(0, pos);
    inVertex->get(1, uv);
    inVertex->get(2, normal);

    PRINTLN(pos);


    mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;

    // TODO: clarify this matrix math
    glPos = PVM * vec4(pos.x, pos.y, pos.z, 1.0);

    vec4 tNormalV4 = modelMatrix * vec4(normal.x, normal.y, normal.z, 0);
    tNormal = vec3(tNormalV4.x, tNormalV4.y, tNormalV4.z);

    vec4 objectWorldPos = modelMatrix * vec4(pos.x, pos.y, pos.z, 1.0);
    tLightPos = lightPosition - vec3(objectWorldPos.x, objectWorldPos.y, objectWorldPos.z);

    PRINTLN(glPos);

    outVertex->set(0, glPos.toVector());
    outVertex->set(1, uv.toVector());
    outVertex->set(2, tNormal);
    outVertex->set(3, tLightPos);
  }

private:
  vec3 lightPosition;
};
