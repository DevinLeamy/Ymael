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

#include "usage/BasicVertexShader.h"

int main() {
  // load model
  std::unique_ptr<Model> model { loadModel("res/B.obj") };

  // create vao
  VertexArrayObject *vao = new VertexArrayObject(); 

  // create attribute buffers
  TBuffer<vec3> *positions = new TBuffer<vec3>(model->getVertices().size());
  TBuffer<vec2> *uvs = new TBuffer<vec2>(model->getUVs().size());
  TBuffer<vec3> *normals = new TBuffer<vec3>(model->getNormals().size());

  // load data into attribute buffers
  for (auto v : model->getVertices())
    positions->bind(v);
  
  for (auto v : model->getUVs())
    uvs->bind(v);
  
  for (auto v : model->getNormals())
    normals->bind(v);
  
  // add attribute buffers to vao
  vao->bind(positions);
  vao->bind(uvs);
  vao->bind(normals);

  // create shader program
  ShaderProgram* sProgram = new ShaderProgram();

  // create shaders
  FragmentShader* fs = new FragmentShader();
  VertexShader* vs = new BasicVertexShader();

  // attach shaders to program
  sProgram->bind(fs);
  sProgram->bind(vs);

  // load everything into the state machine 
  GL->bind(vao);
  GL->bind(sProgram);
  GL->bind(model->getIndices());

  // draw triangles
  GL->draw(model->getIndices().size());


  delete positions;
  delete uvs;
  delete normals;
  delete vao;
  delete fs;
  delete vs;
  delete sProgram;
}

