#pragma once

#include "VertexArrayObject.h"
#include "Triangle.h"

class Rasterizer {
public:
  Rasterizer();
  ~Rasterizer() = default;

  // TODO: should be moved elsewhere
  void divideByW();
  void viewportTransform();

  inline void setVSOutBuffers(VertexArrayObject *vsOutBuffers) { 
    this->vsOutBuffers = vsOutBuffers; 
  }

  inline void setFSInBuffers(VertexArrayObject *fsInBuffers) { 
    this->fsInBuffers = fsInBuffers; 
  }

  inline size_t getFragmentCount() { return fragmentCount; }

  void rasterize(size_t vertices);
  void rasterizeTriangle(size_t v0Index);
  void interpolateAttribute(size_t v0Index, size_t attrIndex, const vec2& point, const Triangle& triangle);

  Triangle getTriangle(size_t v0Index) const;

private:
  VertexArrayObject *vsOutBuffers;
  VertexArrayObject *fsInBuffers;
  
  size_t fragmentCount;
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
