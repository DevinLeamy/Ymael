#pragma once

#include <string>
#include <memory>

#include "Model.h"

/*
Mesh: Single drawable entity.
*/
class ModelLoader {
  ModelLoader();
};

std::unique_ptr<Model> loadModel(std::string modelPath);
