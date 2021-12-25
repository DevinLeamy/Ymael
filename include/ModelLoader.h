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

Model* loadModel(std::string modelPath);
