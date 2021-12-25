#pragma once

/*
OpenGL simulator;
*/

#include <memory>

#include "VertexArrayObject.h"
#include "ShaderProgram.h"

class OpenGL {
public:
  OpenGL() = default; 
  ~OpenGL() = default;

  void bind(VertexArrayObject* vao);
  void bind(ShaderProgram* sProgram);
  void bind(const std::vector<std::vector<int>>& indices);

  void draw(int triangleCnt, bool withIndices = true);

private:
  std::vector<std::vector<int>> indices;
  VertexArrayObject* vao;
  ShaderProgram* sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

