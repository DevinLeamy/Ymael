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
#include "Triangle.h"
#include "Camera.h"

#include "usage/BasicVertexShader.h"
#include "usage/BasicFragmentShader.h"

// Camera camera(vec3(-10, -10, 0), vec3(0, 0, 1), vec3(0, 1, 0));
// Camera camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0.612375, 0.612375, -0.50000));
Camera camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0));
WorldTransform modelWT(vec3(30, 30, 0), vec3(0.0f, 0.0f, 0.0f), 30.0f);

void handleInput();
void initController();

void test();

int main() {
  // test();
  // return 0;
  initController();

  // load model
  DEBUG("LOAD MODEL");
  std::unique_ptr<Model> model { loadModel("res/square.obj") };
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
  vs->setUniform(PROJECTION_MATRIX, Camera::projectionMatrix(90.0, 1.0, -40, 100.0));

  // load everything into the state machine 
  DEBUG("BIND COMPONENTS TO OPENGL STATE MACHINE");
  GL->bind(sProgram);

  // draw triangles
  DEBUG("DRAW TRIANGLES");

  GL->render(vertices);

  // while (1);
  while(1) {
    handleInput();
    modelWT.rotate(vec3(5, 5, 5));
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

void test() {
  vec2 a(0, 0), b(0, 20), c(20, 20), p(19.5f, 10.5f);
  Triangle t (a, b, c);

  std::cout << Triangle::getArea(a, b, c) << " " << Triangle::getArea(a, b, p) << std::endl;
  std::cout << Triangle::getArea(a, p, c) << " " << Triangle::getArea(p, b, c) << std::endl;
}
