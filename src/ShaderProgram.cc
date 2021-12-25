#include <memory>

#include "ShaderProgram.h"

void ShaderProgram::bind(VertexShader* vs) {
  this->vs = vs;
}

void ShaderProgram::bind(FragmentShader* fs) {
  this->fs = fs;
}

void ShaderProgram::run(VertexArrayObject *inStream, int vertexCount) {
  std::unique_ptr<VertexArrayObject> vsOutStream = std::make_unique<VertexArrayObject>();

  for (size_t i = 0; i < vertexCount; ++i)
    vs->run(inStream, vsOutStream.get(), i);
  
  // Run the rasterizer to create a VAO with fragment data

}

void ShaderProgram::run(VertexArrayObject *inStream, const std::vector<std::vector<int>>& indices) {

}
