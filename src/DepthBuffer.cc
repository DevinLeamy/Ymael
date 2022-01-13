#include "DepthBuffer.h"
#include "OpenGL.h"

DepthBuffer::DepthBuffer(): Buffer { CONST::WW * CONST::WH, 1 } {
  reset();
}

void DepthBuffer::reset() {
  std::fill(data.begin(), data.end(), 1.0f);
}
