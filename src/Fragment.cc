#include "Fragment.h"

Fragment::Fragment(): GraphicsObject {} {}

vec3 Fragment::getPosition() const {
  return vec3(attrMap.at(0)->get());
}

vec3 Fragment::getColor() const {
  return vec3(attrMap.at(1)->get());
}

Fragment::Fragment(const std::map<int, Attribute*>& attrMap): GraphicsObject{attrMap} {}
