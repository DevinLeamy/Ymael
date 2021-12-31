#include <algorithm>
#include <memory>

#include "Screen.h"
#include "utility.h"

Screen::Screen(size_t WW, size_t WH): FB{std::make_unique<FrameBuffer>()},
  DB{std::make_unique<DepthBuffer>()}, WW{WW}, WH{WH}
{}

void Screen::loadFragment(Fragment* fragment) {
  loadFragment(fragment->getPosition(), fragment->getColor());
}

void Screen::loadFragment(vec3 coord, vec3 colour) {
  size_t bufferIndex = (size_t) (coord.y * WH + coord.x);

  float curDepth;
  float newDepth = coord.z;

  FB->get(bufferIndex, curDepth);

  if (newDepth < curDepth) {
    updateColour(bufferIndex, colour);
    updateDepth(bufferIndex, newDepth);
  }
}

void Screen::updateColour(size_t bufferIndex, vec3 colour) {
  FB->set(bufferIndex, colour);
}

void Screen::updateDepth(size_t bufferIndex, float depth) {
  DB->set(bufferIndex, depth);
}

void Screen::resetBuffers() {
  DB->reset();
  FB->reset();
}

bool Screen::pixelInView(size_t x, size_t y) const {
  if (x < 0 || x >= WW || y < 0 || y >= WH)
    return false;
  return true;
}
