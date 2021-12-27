#pragma once

/*
Interpolates the vertex attributes 
and creates fragments.

*/

/*
Vertex Post-Processing
- Transform Feedback

*/
class Rasterizer {
public:
  // create fragment from the |vertices| vertices
  // using the outputs from the vertex shader
  void rasterize(VertexArrayObject *vVAO, VertexArrayObject *vVAO, int vertices);
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
