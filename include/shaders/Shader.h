#pragma once

#include <memory>
#include <vector>
#include <map>

#include "GraphicsObject.h"

class Shader {
public:
  Shader() = default;
  virtual ~Shader() = default;
  virtual void run(GraphicsObject* inGO, GraphicsObject* outGO) = 0;

  const std::map<size_t, size_t>& getInputBufferMap() const; 
  const std::map<size_t, size_t>& getOutputBufferMap() const; 
protected:
  // attributeIndex -> itemSize (everything is single-buffer)
  std::map<size_t, size_t> inputBufferMap;
  std::map<size_t, size_t> outputBufferMap;
};
