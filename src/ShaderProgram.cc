#include <memory>

#include "ShaderProgram.h"

void ShaderProgram::bind(std::shared_ptr<VertexShader> vs) {
  this->vs = vs;
}

void ShaderProgram::bind(std::shared_ptr<FragmentShader> fs) {
  this->fs = fs;
}

void ShaderProgram::run(const VertexArrayObject &inStream, int vertexCount) {

}

void ShaderProgram::run(const VertexArrayObject &inStream, std::vector<std::vector<int>> indices) {

}
