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
#include "WorldTransform.h"
#include "Camera.h"

#include "usage/BasicVertexShader.h"
#include "usage/BasicFragmentShader.h"

Camera camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));

int main() {
  WorldTransform modelWT(vec3(80, 40, 0), vec3(0, 0, 0), 20.0f);

  // load model
  DEBUG("LOAD MODEL");
  std::unique_ptr<Model> model { loadModel("res/triangle.obj") };
  // create vao
  DEBUG("CREATE VAO");
  VertexArrayObject *vao = model->getVAO(); 

  PRINT(*vao);

  // create shader program
  DEBUG("CREATE SHADER PROGRAM");
  ShaderProgram* sProgram = new ShaderProgram();

  // create shaders
  DEBUG("CREATE VS AND FS");
  FragmentShader* fs = new BasicFragmentShader();
  VertexShader* vs = new BasicVertexShader();

  sProgram->bind<VertexShader>(vs);
  sProgram->bind<FragmentShader>(fs);

  vs->setUniform(MODEL_MATRIX, modelWT.toMatrix());
  vs->setUniform(VIEW_MATRIX, camera.viewMatrix());
  vs->setUniform(PROJECTION_MATRIX, Camera::projectionMatrix(90.0, 1.0, -100, 200.0));

  // load everything into the state machine 
  DEBUG("BIND COMPONENTS TO OPENGL STATE MACHINE");
  GL->bind(vao);
  GL->bind(sProgram);

  // draw triangles
  DEBUG("DRAW TRIANGLES");

  GL->draw(model->getIndices());
  while(1) {
    modelWT.rotate(vec3(0, 0, 0));
    // modelTransform.rotation.x += 10;
    vs->setUniform(MODEL_MATRIX, modelWT.toMatrix());
    GL->draw(model->getIndices());
  }

  DEBUG("RENDER COMPLETE");
}

