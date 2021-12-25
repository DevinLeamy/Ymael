#pragma once

#include <map>

#include "VertexBufferObject.h"

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
  int nextAttr = 0;
  std::map<int, VertexBufferObject *> attributes;
};
