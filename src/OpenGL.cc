#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"

void OpenGL::bind(std::shared_ptr<VertexArrayObject> vao) {
  this->vao = vao;
}

void OpenGL::bind(std::shared_ptr<ShaderProgram> sProgram) {
  this->sProgram = sProgram;
}

void OpenGL::bind(std::vector<std::vector<int>>& indices) {
  this->indices = indices;
}

void OpenGL::draw(int triangleCnt, bool withIndices) {
  // Render objects to the screen
}

const std::unique_ptr<OpenGL> GL{};
