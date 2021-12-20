#pragma once

#include <memory>
#include <vector>

#include "DataStream.h"
#include "VertexArrayObject.h"

class Shader {
  void run(const VertexArrayObject& inStream, const VertexArrayObject& outStream, int vertex);
};
