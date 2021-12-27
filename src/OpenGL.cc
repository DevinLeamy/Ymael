#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"

void OpenGL::bind(VertexArrayObject* vao) {
  this->vao = vao;
}

void OpenGL::bind(ShaderProgram* sProgram) {
  this->sProgram = sProgram;
}

void OpenGL::draw(int vertices) {
  sProgram->runShader<VertexShader>(vertices);

  // int fragments = rasterizer->rasterize(); or something
  // sProgram->runShader<FragmentShader>(fragments);
}

void OpenGL::draw(int vertices, const std::vector<std::vector<int>>& indices) {
  sProgram->runShader<VertexShader>(indices);

  // int fragments = rasterizer->rasterize(); 
  // sProgram->runShader<FragmentShader>(fragments);
  // create frame buffer from VAO
}


const std::unique_ptr<OpenGL> GL = std::make_unique<OpenGL>();
