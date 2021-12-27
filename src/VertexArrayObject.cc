#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {}

void VertexArrayObject::bind(VertexBufferObject *vbo) {
  attributes[nextAttr++] = vbo;
}

void VertexArrayObject::bind(VertexBufferObject *vbo, int attrIndex) {
  attributes[attrIndex] = vbo;
}

bool VertexArrayObject::attributeEnabled(int attrIndex) const {
  return attributes.count(attrIndex) > 0;
}

std::vector<int> VertexArrayObject::getEnabledAttributes() const {
  std::vector<int> attrIndices;

  for (auto [key, value] : attributes)
    attrIndices.push_back(key);
  
  return attrIndices;
}
