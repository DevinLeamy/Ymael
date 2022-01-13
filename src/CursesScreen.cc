#include <iostream>
#include <string>

#include "CursesScreen.h"
#include "math/math.h"
#include "utility.h"

const int COLOR_ATTR = 1;

CursesScreen::CursesScreen(size_t WW, size_t WH): Screen { WW, WH } {
  initscr();
  curs_set(0);

  initializeColors();

  window = newwin(WH, WW, 0, 0);
  drawBorder();
}

CursesScreen::~CursesScreen() {
  delwin(window);
  endwin();
}

void CursesScreen::initializeColors() const {
  if (has_colors() == FALSE) {
    std::cout << "Error: terminal does not support color" << std::endl;
    exit(1);
  }

  start_color();

  for (int i = 0; i < 8; ++i)
    init_pair(i, i, 0);
}

void CursesScreen::drawBorder() const {
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
}

vec2 CursesScreen::coordsToCursesCoords(const vec2& coords) const {
  return vec2(coords.x, WH - coords.y);
}

void CursesScreen::refresh() {
  wrefresh(window);

  DEBUG("RESET BUFFERS");
  resetBuffers();
}

void CursesScreen::draw() {
  // clear the window
  werase(window);
  
  vec3 pixelColour; 

  for (size_t x = 0; x < WW; ++x) {
    for (size_t y = 0; y < WH; ++y) {
      FB->get(y * WH + x, pixelColour);

      vec2 coords = vec2(x, y);
      vec2 cursesCoords = coordsToCursesCoords(coords);

      drawPixel(cursesCoords, pixelColour);
    }
  }

  drawBorder();
  refresh();
}

void CursesScreen::drawPixel(const vec2& coords, vec3 colour) const {
  if (pixelInView(coords) && colour.y == 100) {
    int lightLevel = (int) colour.z;
    mvwaddch(window, coords.y, coords.x, lightLevels[lightLevel]);
  }
}

// void CursesScreen::setColor(vec3 colour) const {
//   wattron(window, COLOR_PAIR((int) colour.x % 8));
// }
