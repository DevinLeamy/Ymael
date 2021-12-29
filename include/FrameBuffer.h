#pragma once

#include "Buffer.h"

class FrameBuffer: public Buffer {
public:
  FrameBuffer();

  void reset();

  ~FrameBuffer() = default;
};
