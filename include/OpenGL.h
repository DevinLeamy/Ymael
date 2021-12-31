#pragma once

#include <memory>

#include "Rasterizer.h"
#include "Screen.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"

namespace CONST {
  const size_t WW = 400;
  const size_t WH = 400;
}

class OpenGL {
public:
  OpenGL(); 
  ~OpenGL() = default;

  void bind(VertexArrayObject* vao);
  void bind(ShaderProgram* sProgram);

  void draw(int vertices);
  void draw(const std::vector<std::vector<int>>& indices);

private:
  void doDraw();
  std::unique_ptr<Rasterizer> rasterizer;
  std::unique_ptr<Screen> screen;
  VertexArrayObject* vao;
  ShaderProgram* sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

