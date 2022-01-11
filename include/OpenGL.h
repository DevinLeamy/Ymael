#pragma once

#include <memory>

#include "Rasterizer.h"
#include "Screen.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "GTriangle.h"

namespace CONST {
  const size_t WW = 400;
  const size_t WH = 150;
}

class OpenGL {
public:
  OpenGL(); 
  ~OpenGL() = default;

  void bind(ShaderProgram* sProgram);

  void render(const std::vector<Vertex*>& vertices);

private:
  void doDraw();
  std::vector<std::unique_ptr<GTriangle>> primitiveAssembly(const std::vector<std::unique_ptr<Vertex>>& vertices);
  std::unique_ptr<Rasterizer> rasterizer;
  std::unique_ptr<Screen> screen;
  ShaderProgram* sProgram; 
};

extern const std::unique_ptr<OpenGL> GL;

