#include <memory>

#include "OpenGL.h"
#include "utility.h"
#include "CursesScreen.h"
#include "Screen.h"
#include "Vertex.h"
#include "GTriangle.h"

OpenGL::OpenGL() {
  rasterizer = std::make_unique<Rasterizer>();
  screen = std::make_unique<CursesScreen>(CONST::WW, CONST::WH);
  // screen = std::make_unique<Screen>(CONST::WW, CONST::WH);
}

void OpenGL::bind(ShaderProgram* sProgram) { this->sProgram = sProgram; }

void OpenGL::render(const std::vector<Vertex*>& vertices) {
  // (1) run the vertex shader 
  DEBUG("RUN VERTEX SHADER");
  std::vector<std::unique_ptr<Vertex>> tVertices; // t = transformed 

  for (auto inVertex : vertices) {
    std::unique_ptr<Vertex> outVertex = std::make_unique<Vertex>(); 

    sProgram->runShader<VertexShader>(inVertex, outVertex.get());
    tVertices.push_back(std::move(outVertex));
  }
  
  // (2) run the primitive assembly
  DEBUG("RUN PRIMITIVE ASSEMBLY");
  std::vector<std::unique_ptr<GTriangle>> triangles = primitiveAssembly(tVertices);

  for (size_t i = 0; i < triangles.size(); ++i) {
    // (3) run the rasterizer
    DEBUG("RUN RASTERIZER");
    std::vector<std::unique_ptr<Fragment>> fragments = rasterizer->rasterize(triangles[i].get());

    // (4) run the fragment shader
    DEBUG("RUN FRAGMENT SHADER");
    std::vector<std::unique_ptr<Fragment>> tFragments;
    for (size_t j = 0; j < fragments.size(); ++j) {
      std::unique_ptr<Fragment> outFragment = std::make_unique<Fragment>();

      sProgram->runShader<FragmentShader>(fragments[j].get(), outFragment.get());
      tFragments.push_back(std::move(outFragment));
    }

    // (5) load pixels into the frame buffer
    DEBUG("LOAD FRAGMENTS");
    for (size_t j = 0; j < tFragments.size(); ++j)
      screen->loadFragment(tFragments[j].get());
  }

  // (6) display the screen
  DEBUG("DISPLAY");
  screen->draw();
}

std::vector<std::unique_ptr<GTriangle>> OpenGL::primitiveAssembly(const std::vector<std::unique_ptr<Vertex>>& vertices) {
  size_t triangleCount = vertices.size() / 3;
  std::vector<std::unique_ptr<GTriangle>> triangles;

  for (size_t i = 0; i < triangleCount; ++i) {
    Vertex *v0 = vertices[i * 3 + 0].get();
    Vertex *v1 = vertices[i * 3 + 1].get();
    Vertex *v2 = vertices[i * 3 + 2].get();

    std::unique_ptr<GTriangle> triangle = std::make_unique<GTriangle>(v0, v1, v2);
    triangles.push_back(std::move(triangle));
  }

  return std::move(triangles);
}

const std::unique_ptr<OpenGL> GL = std::make_unique<OpenGL>();
