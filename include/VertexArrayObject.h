#pragma once

#include <map>
#include <any>
#include <cassert>

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

  // std::any getAttribute(size_t attribute, size_t index);
  
  // 
  VertexBufferObject *getAttributeBuffer(int attrIndex) {
    assert(attributes.count(attrIndex));

    return attributes[attrIndex];
  }

private:
  int nextAttr = 0;
  std::map<int, VertexBufferObject *> attributes;
};
