#include <memory>
#include <map>

#include "ShaderProgram.h"
#include "shaders/Shader.h"
#include "utility.h"


void ShaderProgram::runShaderPrepare(Shader* shader, int itemCount) {
  // outStream = std::make_unique<VertexArrayObject>();
  outStream = new VertexArrayObject();
  std::map<size_t, size_t> outputBuffersMap = shader->getOutputBufferMap();

  for (auto& [attrIndex, itemSize] : outputBuffersMap)
    // TODO: fix memory leak from buffers
    outStream->bind(new VertexBufferObject { (size_t) itemCount, itemSize }, attrIndex);
}

void ShaderProgram::runShaderCleanup(Shader* shader, int itemCount) {}

void ShaderProgram::setInputVAO(VertexArrayObject* inVAO) { 
  inStream = inVAO;
}

VertexArrayObject* ShaderProgram::getOutputVAO() {
  return outStream;
}
