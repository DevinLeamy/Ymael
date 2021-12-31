#pragma once

#include <vector>
#include <memory>

#include "math/vec2.h"
#include "math/vec3.h"
#include "Vertex.h"

using std::vector;

class Model {
public:
  Model(const vector<vec3>& vertices, const vector<vec2>& uvs, 
        const vector<vec3>& normals, const vector<vector<int>>& indices);

  inline const vector<vector<int>>& getIndices() const { return indices; }
  vector<Vertex*> getVertices() const; 

private:
  vector<std::unique_ptr<Vertex>> vertices; 
  vector<std::unique_ptr<Attribute>> positions; // positions
  vector<std::unique_ptr<Attribute>> uvs;      // texture coords
  vector<std::unique_ptr<Attribute>> normals;  // vertex normals
  vector<vector<int>> indices; // indices
};
