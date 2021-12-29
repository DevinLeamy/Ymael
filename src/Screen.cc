#include <algorithm>

#include "Screen.h"

Screen::Screen(size_t WW, size_t WH): WW{WW}, WH{WH} {}

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

void Screen::swapBuffers() {
  std::swap(aFB, FB);
  std::swap(aDB, DB);
}

void Screen::resetNoneActiveBuffers() {
  DB->reset();
  FB->reset();
}

bool Screen::pixelInView(size_t x, size_t y) const {
  if (x < 0 || x >= WW || y < 0 || y >= WH)
    return false;
  return true;
}