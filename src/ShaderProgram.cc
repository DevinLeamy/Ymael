#include <memory>
#include <map>

#include "ShaderProgram.h"
#include "shaders/Shader.h"


void ShaderProgram::runShaderPrepare(Shader* shader, int itemCount) {
  outStream = std::make_unique<VertexArrayObject>();
  std::map<int, int> outputBuffersMap = shader->getOutputBufferMap();

  for (auto& [attrIndex, itemSize] : outputBuffersMap)
    // TODO: fix memory leak from buffers
    outStream->bind(new VertexBufferObject { itemCount, itemSize }, attrIndex);
}

void ShaderProgram::runShaderCleanup(Shader* shader, int itemCount) {}

void ShaderProgram::setInputVAO(VertexArrayObject* inVAO) { 
  inStream = std::unique_ptr<VertexArrayObject>(inVAO);
}

VertexArrayObject* ShaderProgram::getOutputVAO() {
  return outStream.get();
}
