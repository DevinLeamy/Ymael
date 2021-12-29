#include <iostream>
#include <memory>

#include "math/vec2.h"
#include "OpenGL.h"
#include "ModelLoader.h"
#include "Model.h"
#include "utility.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"
#include "shaders/VertexShader.h"
#include "shaders/FragmentShader.h"
#include "Buffer.h"
#include "Transform.h"

#include "usage/BasicVertexShader.h"
#include "usage/BasicFragmentShader.h"

int main() {
  Transform modelTransform {
    .position = vec3(10, 0, 0),
    .rotation = vec3(0, 0, 0),
    .scale = vec3(20, 20, 20)
  };

  // load model
  DEBUG("LOAD MODEL");
  std::unique_ptr<Model> model { loadModel("res/B.obj") };

  // create vao
  DEBUG("CREATE VAO");
  VertexArrayObject *vao = new VertexArrayObject(); 

  // create attribute buffers
  DEBUG("CREATE ATTRIBUTE BUFFERS");
  VertexBufferObject *positions = new VertexBufferObject(model->getVertices().size(), 3);
  VertexBufferObject *uvs = new VertexBufferObject(model->getUVs().size(), 2);
  VertexBufferObject *normals = new VertexBufferObject(model->getNormals().size(), 3);

  // load data into attribute buffers
  DEBUG("LOAD DATA INTO ATTRIBUTE BUFFERS");
  for (auto v : model->getVertices())
    positions->bind(v);
  
  for (auto v : model->getUVs())
    uvs->bind(v);
  
  for (auto v : model->getNormals())
    normals->bind(v);
  
  // add attribute buffers to vao
  DEBUG("BIND ATTRIBUTE BUFFERS TO VAO");
  vao->bind(positions);
  vao->bind(uvs);
  vao->bind(normals);

  // create shader program
  DEBUG("CREATE SHADER PROGRAM");
  ShaderProgram* sProgram = new ShaderProgram();

  // create shaders
  DEBUG("CREATE VS AND FS");
  FragmentShader* fs = new BasicFragmentShader();
  VertexShader* vs = new BasicVertexShader();

  vs->setUniform(MODEL_MATRIX, createTransformMat(modelTransform));

  // attach shaders to program
  DEBUG("ATTACH SHADERS TO SHADER PROGRAM");
  sProgram->bind<VertexShader>(vs);
  sProgram->bind<FragmentShader>(fs);

  // load everything into the state machine 
  DEBUG("BIND COMPONENTS TO OPENGL STATE MACHINE");
  GL->bind(vao);
  GL->bind(sProgram);

  // draw triangles
  DEBUG("DRAW TRIANGLES");
  GL->draw(model->getIndices());

  DEBUG("RENDER COMPLETE");


  // delete positions;
  // delete uvs;
  // delete normals;
  // delete vao;
  // delete fs;
  // delete vs;
  // delete sProgram;
}

