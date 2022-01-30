#pragma once

#include <ncurses.h>

#include "Screen.h"

class CursesScreen: public Screen {
public:
  CursesScreen(size_t WW, size_t WH);

  void refresh() override;
  void draw() override;

  ~CursesScreen();

private:

  void drawBorder() const;
  void initializeColors() const;
  void drawPixel(const vec2& coords, vec3 colour) const; 
  vec2 coordsToCursesCoords(const vec2& coords) const;
  // void setColor(vec3 colour) const;

  WINDOW *window;
  std::string lightLevels = ".,~;o+=*&%#@";
};



