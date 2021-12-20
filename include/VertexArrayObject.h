#pragma once

#include "Buffer.h" // Perhaps change to a VBO

/*
Holds all the VertexObjectBuffers for all the 
attributes of all the vertices of a model
*/

class VertexArrayObject {
  std::map<int, std::shared_ptr<Buffer>> attributes;

  void bind(const std::shared_ptr<Buffer> vbo);
  void bind(const std::shared_ptr<Buffer> vbo, int attributeIndex);

};
