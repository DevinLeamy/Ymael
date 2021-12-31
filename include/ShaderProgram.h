#pragma once

#include <memory>

#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"
#include "utility.h"

// TODO: this class may be pointless 
class ShaderProgram {
public:
  ShaderProgram() = default;
  ~ShaderProgram() = default;
  
  template <typename T>
  void bind(Shader* shader) { shaders[TYPE_NAME(T)] = shader; }

  template <typename T>
  void runShader(GraphicsObject* inGO, GraphicsObject* outGO) {
    if (shaders.count(TYPE_NAME(T)) == 0) return;

    Shader* shader = shaders[TYPE_NAME(T)];

    DEBUG("RUN SHADER");
    return shader->run(inGO, outGO);
  }
private:
  std::map<std::string, Shader*> shaders;
};
