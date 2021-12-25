#pragma once

#include <vector>

#include "math/vec2.h"
#include "math/vec3.h"

using std::vector;

class Model {
public:
  Model(const vector<vec3>& vertices, const vector<vec2>& uvs, 
        const vector<vec3>& normals, const vector<vector<int>>& indices);

  const vector<vec3>& getVertices() const;
  const vector<vec2>& getUVs() const;
  const vector<vec3>& getNormals() const;
  const vector<vector<int>>& getIndices() const;

private:
  vector<vec3> vertices; // positions
  vector<vec2> uvs;      // texture coords
  vector<vec3> normals;  // vertex normals
  vector<vector<int>> indices; // indices
};
