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

    DEBUG("PREPARE SHADER");
    Shader* shader = shaders[TYPE_NAME(T)];
    runShaderPrepare(shader, indices.size());

    DEBUG("RUN SHADER");
    for (const std::vector<int> attrIndices : indices)
      shader->run(inStream, outStream, attrIndices);
      // shader->run(inStream.get(), outStream.get(), attrIndices);

    DEBUG("CLEANUP SHADER");
    runShaderCleanup(shader, indices.size());
  }

  template <typename T>
  void runShader(int itemCount) {
    if (shaders.count(TYPE_NAME(T)) == 0) return;

    DEBUG("PREPARE SHADER");
    Shader* shader = shaders[TYPE_NAME(T)];
    runShaderPrepare(shader, itemCount);

    DEBUG("RUN SHADER");
    for (int i = 0; i < itemCount; ++i)
      shader->run(inStream, outStream, std::vector<int>(inStream->getBufferCount(), i));
      // shader->run(inStream.get(), outStream.get(), std::vector<int>(inStream->getBufferCount(), i));

    DEBUG("CLEANUP SHADER");
    runShaderCleanup(shader, itemCount);
  }
private:
  void runShaderPrepare(Shader* shader, int itemCount);
  void runShaderCleanup(Shader* shader, int itemCount);

  std::map<std::string, Shader*> shaders;

  // in/out to/from a shader 
  VertexArrayObject* inStream;
  VertexArrayObject* outStream;
  // std::unique_ptr<VertexArrayObject> inStream;
  // std::unique_ptr<VertexArrayObject> outStream; 
};
