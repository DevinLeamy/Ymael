#pragma once

#include "Buffer.h" // Perhaps change to a VBO

/*
Holds all the VertexObjectBuffers for all the 
attributes of all the vertices of a model
*/

class VertexArrayObject {
  // consider using std::variant w/ .index() 
  std::map<int, Buffer>> attributes;

  void bind(const std::shared_ptr<Buffer> vbo);
  void bind(const std::shared_ptr<Buffer> vbo, int attributeIndex);

};
