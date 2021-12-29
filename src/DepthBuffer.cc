#include "DepthBuffer.h"
#include "OpenGL.h"

DepthBuffer::DepthBuffer(): Buffer { CONST::WW * CONST::WH, 1 } {
  for (size_t i = 0; i < data.size(); ++i)
    data[i] = 1.0; // maximum depth
}

void DepthBuffer::reset() {
  for (size_t i = 0; i < data.size(); ++i)
    data[i] = 1.0;
}
