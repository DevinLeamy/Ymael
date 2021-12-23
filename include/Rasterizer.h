#pragma once

/*
Interpolates the vertex attributes 
and creates fragments.

*/
class Rasterizer {
public:
  void rasterize(VertexArrayObject *vertexData, int vertices);
};
