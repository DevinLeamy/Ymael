#pragma once

#include <memory>

#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"
#include "utility.h"

class ShaderProgram {
public:
  ShaderProgram() = default;
  
  template <typename T>
  void bind(Shader* shader) { shaders[TYPE_NAME(T)] = shader; }

  void setInputVAO(VertexArrayObject* inVAO);
  VertexArrayObject* getOutputVAO();

  template <typename T>
  void runShader(const std::vector<std::vector<int>> indices) {
    if (shaders.count(TYPE_NAME(T)) == 0) return;

    Shader* shader = shaders[TYPE_NAME(T)];
    runShaderPrepare(shader, indices.size());

    for (const std::vector<int> attrIndices : indices)
      shader->run(inStream, outStream, attrIndices);

    runShaderCleanup(shader, indices.size());
  }

  template <typename T>
  void runShader(int itemCount) {
    if (shaders.count(TYPE_NAME(T)) == 0) return;

    Shader* shader = shaders[TYPE_NAME(T)];
    runShaderPrepare(shader, itemCount);

    for (int i = 0; i < vertexCount; ++i)
      shader->run(inStream, outStream, i);

    runShaderCleanup(shader, itemCount);
  }
private:
  void runShaderPrepare(Shader* shader, int itemCount);
  void runShaderCleanup(Shader* shader, int itemCount);

  std::map<std::string, Shader*> shaders;

  // in/out to/from a shader 
  std::unique_ptr<VertexArrayObject> inStream;
  std::unique_ptr<VertexArrayObject> outStream; 
};
