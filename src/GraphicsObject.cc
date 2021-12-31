#include <map>
#include <memory>

#include "GraphicsObject.h"
#include "Attribute.h"
#include "utility.h"


GraphicsObject::GraphicsObject() {} 
GraphicsObject::GraphicsObject(const std::map<int, Attribute*>& attrMap): attrMap{attrMap} {}

void GraphicsObject::get(int attrIndex, float& val) const { val = attrMap.at(attrIndex)->getFloat(0); }
void GraphicsObject::get(int attrIndex, vec2& res) const { res = vec2(attrMap.at(attrIndex)->get()); } 
void GraphicsObject::get(int attrIndex, vec3& res) const { res = vec3(attrMap.at(attrIndex)->get()); }
void GraphicsObject::get(int attrIndex, vec4& res) const { res = vec4(attrMap.at(attrIndex)->get()); }

// TODO: check if attribute 
void GraphicsObject::set(int attrIndex, float val) { set(attrIndex, { val }); }
void GraphicsObject::set(int attrIndex, vec2& vec) { set(attrIndex, vec.toVector()); }
void GraphicsObject::set(int attrIndex, vec3& vec) { set(attrIndex, vec.toVector()); } 
void GraphicsObject::set(int attrIndex, vec4& vec) { set(attrIndex, vec.toVector()); }

void GraphicsObject::set(int attrIndex, Attribute* attribute) { attrMap[attrIndex] = attribute; }

void GraphicsObject::set(int attrIndex, const std::vector<float>& attrData) {
  std::unique_ptr<Attribute> attribute = std::make_unique<Attribute>(attrData.size(), attrData);
  attrMap[attrIndex] = attribute.get();
  ownedAttributes.push_back(std::move(attribute));
}

float GraphicsObject::getRawFloat(int attrIndex, int floatIndex) const {
  return attrMap.at(attrIndex)->getFloat(floatIndex);
}

std::vector<int> GraphicsObject::getAttrIndices() const {
  std::vector<int> attrIndices;

  for (auto& [key, value] : attrMap)
    attrIndices.push_back(key);
  
  return attrIndices;
}

void GraphicsObject::setRawFloat(int attrIndex, int floatIndex, float value) {
  attrMap[attrIndex]->setFloat(floatIndex, value);
}

size_t GraphicsObject::getAttributeSize(int attrIndex) {
  return attrMap[attrIndex]->getSize();
}
