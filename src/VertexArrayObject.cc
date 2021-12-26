#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {}

void VertexArrayObject::bind(VertexBufferObject *vbo) {
  attributes[nextAttr++] = vbo;
}

void VertexArrayObject::bind(VertexBufferObject *vbo, int attrIndex) {
  attributes[attrIndex] = vbo;
}

// std::any VertexArrayObject::getAttribute(size_t attribute, size_t index) {
//   if (!attributes.count(attribute)) {
//     std::cout << "ERROR: attribute {" << attribute << "} does not exist";
//     exit(1);
//   }

//   attributes[attribute]->get() 
// }
