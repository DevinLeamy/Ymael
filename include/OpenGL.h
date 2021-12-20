#pragma once

/*
OpenGL simulator;
*/

#include <memory>

#include "VertexArrayObject.h"

class OpenGL {
  OpenGL() = default; 
  ~OpenGL() = default;

public:
  void bind(std::shared_ptr<VertexArrayObject> vao);

  void draw(int triangleCount);


private:
  std::shared_ptr<VertexArrayObject> vao;

};

extern const std::unique_ptr<OpenGL> GL;

