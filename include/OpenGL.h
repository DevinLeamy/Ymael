#pragma once

/*
OpenGL simulator;
*/

#include <memory>

#include "VertexArrayObject.h"
#include "ShaderProgram.h"

class OpenGL {
  OpenGL() = default; 
  ~OpenGL() = default;

public:
  void bind(std::shared_ptr<VertexArrayObject> vao);
  void bind(std::shared_ptr<ShaderProgram> sProgram);
  void bind(std::vector<std::vector<int>>& indices);

  void draw(int triangleCnt, bool withIndices = true);

private:
  std::vector<std::vector<int>>& indices;
  std::shared_ptr<VertexArrayObject> vao;
  std::shared_ptr<ShaderProgram> sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

