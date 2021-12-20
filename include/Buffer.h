#pragma once

#include <vector>

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

class Buffer {
  Buffer(std::vector<double> data, std::vector<double> indices);

  void bind(vec3& vec) {
    indices[iIndex] = index;
    data[index++] = vec.x;
    data[index++] = vec.y;
    data[index++] = vec.z;
  }

  void get(size_t index, vec3& res) const {
    res.x = data[indices[index]]; 
    res.y = data[indices[index] + 1]; 
    res.z = data[indices[index] + 2]; 
  }

  void set(size_t index, ve3& vec) {
    data[indices[index]] = vec.x;
    data[indices[index] + 1] = vec.y;
    data[indices[index] + 2] = vec.z;
  }

private:
  size_t dIndex = 0;            // current vertex
  size_t iIndex = 0; 
  std::vector<double> data;    // raw data
  std::vector<double> indices; // vertex indices
  
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

