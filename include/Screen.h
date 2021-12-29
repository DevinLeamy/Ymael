#pragma once

#include <memory>

#include "FrameBuffer.h"
#include "DepthBuffer.h"
#include "math/math.h"

class Screen {
public:
  Screen(size_t WW, size_t WH);

  // TODO: make pure virtual
  virtual void draw() {};

  void loadFragment(vec3 coord, vec3 colour); 

  virtual ~Screen() = default;

protected:
  void swapBuffers();
  void resetNoneActiveBuffers();
  void updateColour(size_t bufferIndex, vec3 colour);
  void updateDepth(size_t bufferIndex, float depth);

  bool pixelInView(size_t x, size_t y) const; 

  // a -> actively drawing to the screen
  std::unique_ptr<FrameBuffer> aFB;  
  std::unique_ptr<FrameBuffer> FB;

  std::unique_ptr<DepthBuffer> aDB;
  std::unique_ptr<DepthBuffer> DB;

  size_t const WW;
  size_t const WH;
};
