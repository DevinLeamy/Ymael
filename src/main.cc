#include <iostream>
#include <memory>
#include <ncurses.h>

#include "math/vec2.h"
#include "OpenGL.h"
#include "ModelLoader.h"
#include "Model.h"
#include "utility.h"
#include "ShaderProgram.h"
#include "shaders/VertexShader.h"
#include "shaders/FragmentShader.h"
#include "Buffer.h"
#include "WorldTransform.h"
#include "Camera.h"

#include "usage/BasicVertexShader.h"
#include "usage/BasicFragmentShader.h"

// Camera camera(vec3(-10, -10, 0), vec3(0, 0, 1), vec3(0, 1, 0));
Camera camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
WorldTransform modelWT(vec3(0, 0, 0), vec3(0, 0, 0.0f), 20.0f);

void handleInput();
void initController();

int main() {
  initController();

  // load model
  DEBUG("LOAD MODEL");
  std::unique_ptr<Model> model { loadModel("res/triangle.obj") };
  // create vao
  DEBUG("CREATE VERTICES");
  std::vector<Vertex*> vertices = model->getVertices(); 

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
  vs->setUniform(PROJECTION_MATRIX, Camera::projectionMatrix(90.0, 1.0, 0, 200.0));

  // load everything into the state machine 
  DEBUG("BIND COMPONENTS TO OPENGL STATE MACHINE");
  GL->bind(sProgram);

  // draw triangles
  DEBUG("DRAW TRIANGLES");

  GL->render(vertices);

  while (1);
  while(1) {
    handleInput();
    // modelWT.rotate(vec3(0, 0, 1));
    vs->setUniform(MODEL_MATRIX, modelWT.toMatrix());
    vs->setUniform(VIEW_MATRIX, camera.viewMatrix());
    GL->render(vertices);
  }

  DEBUG("RENDER COMPLETE");
}


void initController() {
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, TRUE);
}

void handleInput() {
  char c = getch();

  flushinp();
  
  camera.update_temp(c);
}
