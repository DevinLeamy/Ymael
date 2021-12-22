#pragma once

#include <memory>

#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"

class ShaderProgram {
public:
  void bind(std::shared_ptr<VertexShader> vs);
  void bind(std::shared_ptr<FragmentShader> fs);

  void run(const VertexArrayObject &inStream, int vertexCount);
  void run(const VertexArrayObject &inStream, std::vector<std::vector<int>> indices);
private:
  std::shared_ptr<VertexShader> vs;
  std::shared_ptr<FragmentShader> fs;
};
