#include <iostream>
#include <string>

#include "CursesScreen.h"
#include "utility.h"

const int COLOR_ATTR = 1;

CursesScreen::CursesScreen(size_t WW, size_t WH): Screen { WW, WH } {
  initscr();

  if (has_colors() == FALSE) {
    std::cout << "Error: terminal does not support color" << std::endl;
    exit(1);
  }
  curs_set(0);
  start_color();

  for (int i = 0; i < 8; ++i)
    init_pair(i, i, 0);

  window = newwin(WH, WW, 0, 0);
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
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

      // TODO: make transformation to CursesScreen coords a function
      drawPixel(x, WH - y, pixelColour);
      // wrefresh(window);
    }
  }

  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(window);

  DEBUG("RESET BUFFERS");
  resetBuffers();
}

void CursesScreen::drawPixel(size_t x, size_t y, vec3 colour) const {
  std::string lightLevels = "@#%&*=+o;~,.";
  
  if (pixelInView(x, y) && colour.y == 100) {
    // setColor(colour);

    int lightLevel = (int) colour.z;
    
    mvwaddch(window, y, x, lightLevels[lightLevel]);

    // wattroff(window, COLOR_PAIR(COLOR_ATTR));
  }
}

void CursesScreen::setColor(vec3 colour) const {
  // vec3 cursesColour(
  //   1000.0f * colour.x / 255.0f,
  //   1000.0f * colour.y / 255.0f,
  //   1000.0f * colour.z / 255.0f
  // );


  wattron(window, COLOR_PAIR((int) colour.x % 8));
  // wattron(window, COLOR_PAIR(2));
}
