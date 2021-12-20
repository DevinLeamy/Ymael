#pragma once

#include <vector>

#include "math/vec2.h"
#include "math/vec3.h"

using std::vector;

class Model {
public:
  Model(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<vector<vector<int>>> indices);

  const vector<vec3> &getVertices() const;
  const vector<vec2> &getUVs() const;
  const vector<vec3> &getNormals() const;
  // vector<vec3> getVertices() const;

private:
  vector<vec3> vertices; // positions
  vector<vec2> uvs;      // texture coords
  vector<vec3> normals;  // vertex normals
  vector<vector<vector<int>>> indices; // indices
};
