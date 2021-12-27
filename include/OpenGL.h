#pragma once

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

  OpenGL() = default; 
  ~OpenGL() = default;

  void bind(VertexArrayObject* vao);
  void bind(ShaderProgram* sProgram);
  void bind(const std::vector<std::vector<int>>& indices);

  void draw(int vertices);
  void draw(int vertices, const std::vector<std::vector<int>>& indices);

private:
  VertexArrayObject* vao;
  ShaderProgram* sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

