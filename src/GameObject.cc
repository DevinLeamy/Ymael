#pragma once

#include "GameObject.h"
#include "WorldTransform.h"
#include "Model.h"
#include "shaders/FragmentShader.h"
#include "shaders/VertexShader.h"
#include "ShaderProgram.h"
#include "OpenGL.h"
#include "math/math.h"

GameObject::GameObject(WorldTransform transform, Model* model, VertexShader *vs, FragmentShader* fs):
  transform{transform}, model{model}, vs{vs}, fs{fs}, shaderProg{std::make_unique<ShaderProgram>()} 
{
  shaderProg->bind<VertexShader>(vs);
  shaderProg->bind<FragmentShader>(fs);
}

void GameObject::render() const {
  GL->bind(shaderProg.get());
  GL->render(model->getVertices());
}

void GameObject::update() {
  transform.rotate(vec3(5, 5, 5));
  onUpdate();

  vs->setUniform(MODEL_MATRIX, transform.toMatrix());
}
