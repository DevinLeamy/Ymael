#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"

void OpenGL::bind(VertexArrayObject* vao) {
  this->vao = vao;
}

void OpenGL::bind(ShaderProgram* sProgram) {
  this->sProgram = sProgram;
}

void OpenGL::bind(std::vector<std::vector<int>>& indices) {
  this->indices = indices;
}

void OpenGL::draw(int triangleCnt, bool withIndices) {
  if (withIndices)
    sProgram->run(vao, indices);
  else
    sProgram->run(vao, triangleCnt);
}


const std::unique_ptr<OpenGL> GL{};
