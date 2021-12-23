#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {}

void VertexArrayObject::bind(VertexBufferObject *vbo) {
  attributes[nextAttr++] = vbo;
}

void VertexArrayObject::bind(VertexBufferObject *vbo, int attrIndex) {
  attributes[attrIndex] = vbo;
}
