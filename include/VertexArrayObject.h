#pragma once

#include "Buffer.h" // Perhaps change to a VBO
#include "VertexBufferObject.h"
#include <map>

/*
Holds all the VertexObjectBuffers for all the 
attributes of all the vertices of a model
*/

class VertexArrayObject {
public:
  VertexArrayObject();
  // consider using std::variant w/ .index() 

  void bind(VertexBufferObject *vbo);
  void bind(VertexBufferObject *vbo, int attrIndex);

private:
  int nextAttr;
  std::map<int, VertexBufferObject *> attributes;
};
