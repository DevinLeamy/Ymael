#include <cassert>

#include "GTriangle.h"
#include "Vertex.h"
#include "math/math.h"
#include "Fragment.h"
#include "utility.h"

#define POSITION_ATTR 0

GTriangle::GTriangle(Vertex* a, Vertex* b, Vertex* c): Triangle{}, p_a{a}, p_b{b}, p_c{c}, attributes{a->getAttrIndices()} {
  vec4 aPos = a->getPosition();
  vec4 bPos = b->getPosition();
  vec4 cPos = c->getPosition();

  this->a = vec2(aPos.x, aPos.y);
  this->b = vec2(bPos.x, bPos.y);
  this->c = vec2(cPos.x, cPos.y);
}

void GTriangle::interpolate(const vec2& point, Fragment* fragment) const {
  // interpolate position
  {
    vec4 p0 = p_a->getPosition();
    vec4 p1 = p_b->getPosition();
    vec4 p2 = p_c->getPosition(); 

    float interpolatedZ = interpolateFloat(vec3(p0.z, p1.z, p2.z), point);

    vec4 interpolatedPos = vec4(point.x, point.y, interpolatedZ, 1.0f);
    fragment->set(POSITION_ATTR, interpolatedPos); 
  }

  // interpolate other attributes
  {
    for (int attrIndex : attributes) {
      if (attrIndex == POSITION_ATTR) continue; 
      std::vector<float> attribute = interpolateAttribute(point, attrIndex);
      fragment->set(attrIndex, attribute);
    }
  }
}

std::vector<float> GTriangle::interpolateAttribute(const vec2& point, int attrIndex) const {
  assert(attrIndex != POSITION_ATTR);
  std::vector<float> attribute;

  // the size of an attribute an a given index should be the same 
  // across all vertices
  size_t attrSize = p_a->getAttributeSize(attrIndex);

  for (size_t i = 0; i < attrSize; ++i) {
    float f0 = p_a->getRawFloat(attrIndex, i);
    float f1 = p_b->getRawFloat(attrIndex, i);
    float f2 = p_c->getRawFloat(attrIndex, i);

    float interpolated = interpolateFloat(vec3(f0, f1, f2), point);
    attribute.push_back(interpolated);
  }

  return attribute;
}


