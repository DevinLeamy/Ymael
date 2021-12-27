#include <memory>

#include "OpenGL.h"
#include "VertexArrayObject.h"
#include "utility.h"

OpenGL::OpenGL() {
  rasterizer = std::make_unique<Rasterizer>();
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
  std::unique_ptr<VertexArrayObject> fragmentBuffers = std::make_unique<VertexArrayObject>();
  int bufferSize = WH * WW;
  int outputBufferSize;

  // create rasterizer/fragment shader output/input buffers 
  DEBUG("CREATE RASTERIZER OUTPUT BUFFERS");
  VertexArrayObject* outputVAO = sProgram->getOutputVAO();
  for (int attrIndex : outputVAO->getEnabledAttributes()) {
    VertexBufferObject* outputBuffer = outputVAO->getAttributeBuffer(attrIndex);
    VertexBufferObject* fragmentBuffer = new VertexBufferObject(bufferSize, outputBuffer->getItemSize());

    outputBufferSize = outputBuffer->getSize();

    outputVAO->bind(fragmentBuffer, attrIndex);
  }

  DEBUG("RASTERIZE TRIANGLES");
  int fragments = rasterizer->rasterize(outputVAO, fragmentBuffers.get(), outputBufferSize);

  assert(fragments <= bufferSize);

  DEBUG("RUN FRAGMENT SHADER");
  sProgram->setInputVAO(fragmentBuffers.get());
  sProgram->runShader<FragmentShader>(fragments);
}

const std::unique_ptr<OpenGL> GL = std::make_unique<OpenGL>();
