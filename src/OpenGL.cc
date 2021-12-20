#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"

void OpenGL::bind(std::shared_ptr<VertexArrayObject> vao) {
  this->vao = vao;
}

const std::unique_ptr<OpenGL> GL{};
