#pragma once

#include <vector>
#include <memory.h>

#include "math/vec2.h"
#include "math/vec3.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

using std::vector;

class Model {
public:
  Model(const vector<vec3>& vertices, const vector<vec2>& uvs, 
        const vector<vec3>& normals, const vector<vector<int>>& indices);

  inline const vector<vec3>& getVertices() const { return vertices; }
  inline const vector<vec2>& getUVs() const { return uvs; }
  inline const vector<vec3>& getNormals() const { return normals; }
  inline const vector<vector<int>>& getIndices() const { return indices; }
  inline VertexArrayObject *getVAO() const { return vao.get(); }

private:
  std::unique_ptr<VertexArrayObject> vao;
  vector<vec3> vertices; // positions
  vector<vec2> uvs;      // texture coords
  vector<vec3> normals;  // vertex normals
  vector<vector<int>> indices; // indices
};
