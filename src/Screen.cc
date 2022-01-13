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

size_t Screen::getBufferIndex(size_t x, size_t y) const {
  return y * WH + x;
}

void Screen::loadFragment(vec3 coord, vec3 colour) {
  size_t bufferIndex = getBufferIndex((size_t) coord.x, (size_t) coord.y);

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

bool Screen::pixelInView(const vec2& coords) const {
  if (coords.x < 0 || coords.x >= WW || coords.y < 0 || coords.y >= WH)
    return false;
  return true;
}
