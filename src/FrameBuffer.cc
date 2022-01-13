#include "FrameBuffer.h"
#include "OpenGL.h"

// all cells are initialized to be white
FrameBuffer::FrameBuffer(): Buffer { CONST::WW * CONST::WH, 3 } {
  reset();
}

void FrameBuffer::reset() {
  std::fill(data.begin(), data.end(), 255.0f);
}



