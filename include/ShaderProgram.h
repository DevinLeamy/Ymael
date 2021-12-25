#pragma once

#include <memory>

#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"

class ShaderProgram {
public:
  ShaderProgram() = default;
  
  void bind(VertexShader* vs);
  void bind(FragmentShader* fs);

  void run(VertexArrayObject *inStream, int vertexCount);
  void run(VertexArrayObject *inStream, const std::vector<std::vector<int>>& indices);
private:
  VertexShader* vs;
  FragmentShader* fs;
};
