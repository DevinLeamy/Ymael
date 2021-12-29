#pragma once

#include "Buffer.h"

class DepthBuffer: public Buffer {
public:
  DepthBuffer();

  void reset();

  ~DepthBuffer() = default;
};
