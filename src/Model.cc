#include <vector>

#include "Model.h"
#include "math/vec2.h"
#include "math/vec3.h"

using std::vector;

Model::Model(const vector<vec3>& vertices, const vector<vec2>& uvs, 
             const vector<vec3>& normals, const vector<vector<int>>& indices):
  vertices{vertices}, uvs{uvs}, normals{normals}, indices{indices} 
{}

const vector<vec3>& Model::getVertices() const { return vertices; }

const vector<vec2>& Model::getUVs() const { return uvs; }

const vector<vec3>& Model::getNormals() const { return normals; }

const vector<vector<int>>& Model::getIndices() const { return indices; }
