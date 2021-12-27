#include "VertexArrayObject.h"
#include "utility.h"

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

VertexBufferObject* VertexArrayObject::getAttributeBuffer(int attrIndex) {
  assert(attributes.count(attrIndex));

  return attributes[attrIndex];
}

int VertexArrayObject::getBufferCount() const {
  return attributes.size();
}

std::vector<int> VertexArrayObject::getEnabledAttributes() const {
  std::vector<int> attrIndices;

  for (auto [key, value] : attributes)
    attrIndices.push_back(key);
  
  return attrIndices;
}
