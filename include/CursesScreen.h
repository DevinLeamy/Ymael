#pragma once

#include <ncurses.h>

#include "Screen.h"

class CursesScreen: public Screen {
public:
  CursesScreen(size_t WW, size_t WH);

  void draw() override;

  ~CursesScreen();

private:
  void drawPixel(size_t x, size_t y, vec3 colour) const; 
  WINDOW *window;
};



