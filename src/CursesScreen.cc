#include <iostream>
#include <string>

#include "CursesScreen.h"
#include "utility.h"

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
  // clear the window
  werase(window);
  
  vec3 pixelColour; 

  for (size_t x = 0; x < WW; ++x) {
    for (size_t y = 0; y < WH; ++y) {
      FB->get(y * WH + x, pixelColour);

      drawPixel(x, y, pixelColour);
    }
  }

  wrefresh(window);


  DEBUG("SWAP BUFFERS");
  swapBuffers();
  DEBUG("RESET BUFFERS");
  resetNoneActiveBuffers();
}

void CursesScreen::drawPixel(size_t x, size_t y, vec3 colour) const {
  std::string shades = ".o*";
  if (pixelInView(x, y) && colour.x < shades.size())
    mvwaddch(window, y, x, shades[colour.x]);
}
