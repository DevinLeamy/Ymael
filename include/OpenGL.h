#pragma once

#include "Rasterizer.h"

/*
OpenGL simulator;
*/

#include <memory>

#include "VertexArrayObject.h"
#include "ShaderProgram.h"

class OpenGL {
public:
  const size_t WW = 800;
  const size_t WH = 800;

  OpenGL(); 
  ~OpenGL() = default;

  void bind(VertexArrayObject* vao);
  void bind(ShaderProgram* sProgram);

  void draw(int vertices);
  void draw(const std::vector<std::vector<int>>& indices);

private:
  void doDraw();
  std::unique_ptr<Rasterizer> rasterizer;
  VertexArrayObject* vao;
  ShaderProgram* sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

