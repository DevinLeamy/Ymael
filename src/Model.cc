#include <vector>
#include <memory>

#include "Model.h"
#include "math/vec2.h"
#include "math/vec3.h"

using std::vector;

Model::Model(const vector<vec3>& vertices, const vector<vec2>& uvs, 
             const vector<vec3>& normals, const vector<vector<int>>& indices):
  vertices{vertices}, uvs{uvs}, normals{normals}, indices{indices} 
{
  vao = std::make_unique<VertexArrayObject>();

  VertexBufferObject *posVBO = new VertexBufferObject(vertices.size(), 3);
  VertexBufferObject *uvVBO = new VertexBufferObject(uvs.size(), 2);
  VertexBufferObject *nVBO = new VertexBufferObject(normals.size(), 3);

  vao->bind(posVBO);
  vao->bind(uvVBO);
  vao->bind(nVBO);

  // load attribute data into the buffers
  for (vec3 v : vertices) posVBO->bind(v);
  for (vec2 u : uvs) uvVBO->bind(u);
  for (vec3 n : normals ) nVBO->bind(n);
}

