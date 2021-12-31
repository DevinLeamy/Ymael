#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Attribute.h"
#include "math/math.h"

class GraphicsObject {
public:
  GraphicsObject();
  GraphicsObject(const std::map<int, Attribute*>& attrMap);

  void get(int attrIndex, float& val) const;
  void get(int attrIndex, vec2& res) const; 
  void get(int attrIndex, vec3& res) const;
  void get(int attrIndex, vec4& res) const;

  void set(int attrIndex, float val);
  void set(int attrIndex, vec2& vec); 
  void set(int attrIndex, vec3& vec); 
  void set(int attrIndex, vec4& vec); 

  void set(int attrIndex, const std::vector<float>& attrData);
  void set(int attrIndex, Attribute* attribute);

  float getRawFloat(int attrIndex, int floatIndex) const;
  void setRawFloat(int attrIndex, int floatIndex, float value);

  std::vector<int> getAttrIndices() const;
  size_t getAttributeSize(int attrIndex);

  virtual ~GraphicsObject() = default;

protected:
  // TODO: perhaps use std::shared_ptr everywhere?
  std::vector<std::unique_ptr<Attribute>> ownedAttributes;
  std::map<int, Attribute*> attrMap;
};
