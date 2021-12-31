#pragma once

#include "GTriangle.h"
#include "Fragment.h"

class Rasterizer {
public:
  Rasterizer();
  ~Rasterizer() = default;

  // TODO: should be moved elsewhere
  void divideByW();
  void viewportTransform();

  std::vector<std::unique_ptr<Fragment>> rasterize(GTriangle* triangle) const;
};

/*
User defines the attributes of the vertex shader, and accesses them 
in the VS using the indices they picked.

User output attributes of the vertex shader.

User accesses the attributes interpolated by the rasterizer using the 
indices they picked for the VS outputs.

Rasterizer:
- All positions are in screen space [0, WW] [0, WH] 
- They are convered to screen space when put inside the frame buffer
*/

/*
Interpolates the vertex attributes 
and creates fragments.

*/

/*
Vertex Post-Processing
- Transform Feedback

*/
