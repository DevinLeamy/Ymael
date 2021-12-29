#include "FrameBuffer.h"
#include "OpenGL.h"

// all cells are initialized to be white
FrameBuffer::FrameBuffer(): Buffer { CONST::WW * CONST::WH, 3 } {
  for (size_t i = 0; i < data.size(); ++i)
    data[i] = 255.0;
}

void FrameBuffer::reset() {
  for (size_t i = 0; i < data.size(); ++i)
    data[i] = 255.0;
}



