#pragma once

#include <memory>

#include "WorldTransform.h"
#include "Model.h"
#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"
#include "ShaderProgram.h"

class GameObject {
public:
  GameObject(WorldTransform transform, Model* model, VertexShader *vs, FragmentShader* fs);

  GameObject(const GameObject& other) = delete;
  GameObject(GameObject&& other) = delete;

  GameObject operator=(const GameObject& other) = delete;
  GameObject operator=(GameObject &&other) = delete;

  void update();

  void render() const;

  ~GameObject() = default;

private:
  virtual void onUpdate() {};

  WorldTransform transform; 
  Model* model;
  VertexShader* vs;
  FragmentShader* fs;
  std::unique_ptr<ShaderProgram> shaderProg;
};
