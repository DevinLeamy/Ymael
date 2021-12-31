#include "Vertex.h"
#include "GraphicsObject.h"
#include "math/math.h"

Vertex::Vertex(): GraphicsObject{} {}

vec4 Vertex::getPosition() const {
  return vec4(attrMap.at(0)->get());
}

Vertex::Vertex(const std::map<int, Attribute*>& attrMap): GraphicsObject{attrMap} {}
