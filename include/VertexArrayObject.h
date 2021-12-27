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

  void bind(VertexBufferObject *vbo);
  void bind(VertexBufferObject *vbo, int attrIndex);

  VertexBufferObject *getAttributeBuffer(int attrIndex); 

  bool attributeEnabled(int attrIndex) const; 
  std::vector<int> getEnabledAttributes() const;

  int getBufferCount() const;

private:
  int nextAttr = 0;
  std::map<int, VertexBufferObject *> attributes;
};
