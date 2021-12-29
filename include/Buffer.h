#pragma once

#include <vector>
#include "math/math.h"


class Buffer {
public:
  Buffer(size_t itemCnt, size_t itemSize);
  Buffer(std::vector<float> data, size_t itemSize);

  void bind(float val);
  void bind(vec2& vec);
  void bind(vec3& vec); 
  void bind(vec4& vec);

  void get(size_t itemIndex, float& val) const;
  void get(size_t itemIndex, vec2& res) const; 
  void get(size_t itemIndex, vec3& res) const;
  void get(size_t itemIndex, vec4& res) const;

  void set(size_t itemIndex, float val);
  void set(size_t itemIndex, vec2& vec); 
  void set(size_t itemIndex, vec3& vec); 
  void set(size_t itemIndex, vec4& vec); 

  float getRawFloat(size_t rawIndex) const; 
  void setRawFloat(size_t rawIndex, float val);

  size_t getRawSize() const;
  size_t getSize() const;
  size_t getItemSize() const;

  virtual ~Buffer() = default;

protected:
  size_t rawIndex = 0; // index of the next float
  size_t itemSize; // floats in each value
  std::vector<float> data; // raw data

  void bind(const std::vector<float> vals);
  std::vector<float> getSegment(size_t itemIndex, size_t floatCnt) const;
  void set(size_t itemIndex, const std::vector<float>& vals);

  size_t getRawIndex(size_t itemIndex) const;
};

/*
shaderCode(vector<std::shared_ptr<DataStream>> attributes, vector<std::shared_ptr<DataStream>> outputStream) {
  vec3 pos;
  color color;
  attributes[0]->Get(pos);
  attributes[1]->Get(color);
  vec3 transformedPos = transformMatrix * pos;
  outputStream[0]->Set()
}
*/


/*
Used to create a vertex specification.
- The VS's user-define input variables defines the list of expected vertex attributes
for that shader, where each attribute is mapped to each user-defined input variable.
- For each attributes in the shader, you must provide an array of data for that attribute.
  - All these arrays must be the same length
  - Ex:
    - Array of 10 positions (position)
    - Array of 10 colours (colour)
    - Array of 10 light-levels (light)
    - When the shader is used, it will use:
      - (position[i - i + 2], colour[i - i + 2], light[i - i + 2]) to create a triangle primitive
        - (i, i+1, i+2) could be ordered values (1, 2, 3) or indices (idx[i], idx[i+1], idx[i+2])
      - NOTE: this only happens if we specify that we are drawing a triangle primitive. 
- Two ways of rendering with arrays of vertices:
  1. Generate a stream in the array's order.
  2. Use a list of indices to define the order.  
    - Indices control what order the vertices are received in.
    - Can specify the same array element (perhaps the same point) more than once.
Operations:
- Bind(x)
  - Add the data of value x into the data list at positions [i - size(x)]
    - data[i]   = x[0]
    - data[i+1] = x[1]
    - etc...
  - Store indices[currentIndex] = startIndex
  - Store indices[nextIndex]    = startIndex + size(x)
- Get(index, result)
  - Set the data at the index to result.
    - result[0] = data[indices[index]]
    - result[1] = data[indices[index] + 1]
    - etc...
- Set(index, value)
  - Set the data at the index to the value
    - data[indices[index]]   = value[0]
    - data[indices[index]+1] = value[1]
    - etc...
*/
