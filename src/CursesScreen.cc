#include "CursesScreen.h"
#include <iostream>

CursesScreen::CursesScreen(size_t WW, size_t WH): Screen { WW, WH } {
  initscr();
  curs_set(0);

  window = newwin(WH, WW, 0, 0);
}

CursesScreen::~CursesScreen() {
  delwin(window);
  endwin();
}

void CursesScreen::draw() {
  vec3 pixelColour; 

  for (size_t x = 0; x < WW; ++x) {
    for (size_t y = 0; y < WH; ++y) {
      FB->get(y * WH + x, pixelColour);

      drawPixel(x, y, pixelColour);
    }
  }

  wrefresh(window);

  swapBuffers();
  resetNoneActiveBuffers();
}

void CursesScreen::drawPixel(size_t x, size_t y, vec3 colour) const {
  if (pixelInView(x, y))
    mvwaddch(window, y, x, '#');
}
