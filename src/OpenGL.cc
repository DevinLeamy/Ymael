#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"
#include "utility.h"
#include "CursesScreen.h"
#include "Screen.h"

OpenGL::OpenGL() {
  rasterizer = std::make_unique<Rasterizer>();
  screen = std::make_unique<CursesScreen>(CONST::WW, CONST::WH);
  // screen = std::make_unique<Screen>(CONST::WW, CONST::WH);
}

void OpenGL::bind(VertexArrayObject* vao) { this->vao = vao; }
void OpenGL::bind(ShaderProgram* sProgram) { this->sProgram = sProgram; }

void OpenGL::draw(int vertices) {
  DEBUG("RUN VERTEX SHADER");
  sProgram->setInputVAO(vao);
  sProgram->runShader<VertexShader>(vertices);

  // everything beyond the vertex shader
  doDraw();
}

void OpenGL::draw(const std::vector<std::vector<int>>& indices) {
  DEBUG("RUN VERTEX SHADER");
  sProgram->setInputVAO(vao);
  sProgram->runShader<VertexShader>(indices);

  // everything beyond the vertex shader
  doDraw();
}

void OpenGL::doDraw() {
  // TODO: make this a static buffer?
  static std::unique_ptr<VertexArrayObject> fragmentBuffers = std::make_unique<VertexArrayObject>();
  int bufferSize = CONST::WH * CONST::WW;
  int outputBufferSize;

  // create rasterizer/fragment shader output/input buffers 
  DEBUG("CREATE RASTERIZER OUTPUT BUFFERS");
  VertexArrayObject* outputVAO = sProgram->getOutputVAO();

  PRINT(*outputVAO);

  rasterizer->setVSOutBuffers(outputVAO);
  rasterizer->setFSInBuffers(fragmentBuffers.get());
  
  /*
  Note:
  This assumes that the output buffers from the vertex shader are equivalent
  (as far as the attr->itemSize of each buffer) to the input buffer of the 
  fragment shader.

  In other words, the rasterizer should only change the number of items  
  in each buffer, and nothing else.
  */

  for (int attrIndex : outputVAO->getEnabledAttributes()) {
    VertexBufferObject* outputBuffer = outputVAO->getAttributeBuffer(attrIndex);
    VertexBufferObject* fragmentBuffer = new VertexBufferObject(bufferSize, outputBuffer->getItemSize());

    outputBufferSize = outputBuffer->getSize();

    fragmentBuffers->bind(fragmentBuffer, attrIndex);
  }

  DEBUG("RASTERIZE TRIANGLES");
  rasterizer->rasterize(outputBufferSize);

  size_t fragments = rasterizer->getFragmentCount();

  DEBUG("FRAGMENT COUNT: " << fragments);

  // TODO: view transform

  DEBUG("RUN FRAGMENT SHADER");
  sProgram->setInputVAO(fragmentBuffers.get());
  sProgram->runShader<FragmentShader>(fragments);

  DEBUG("ACCESS FS OUTPUT BUFFERS");
  outputVAO = sProgram->getOutputVAO();
  DEBUG(*outputVAO);

  VertexBufferObject *screenCoordB = outputVAO->getAttributeBuffer(0);
  VertexBufferObject *colourB = outputVAO->getAttributeBuffer(1);

  DEBUG("LOAD FRAGMENTS INTO SCREEN BUFFERS");
  for (size_t i = 0; i < fragments; ++i) {
    vec3 screenCoord;
    vec3 colour;

    screenCoordB->get(i, screenCoord);
    colourB->get(i, colour);

    // PRINTLN(i);
    screen->loadFragment(screenCoord, colour);
  }

  DEBUG("DRAW TO SCREEN");
  screen->draw();

  DEBUG("RENDER COMPLETE");
}

const std::unique_ptr<OpenGL> GL = std::make_unique<OpenGL>();
