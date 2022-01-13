#include <vector>
#include <memory>

#include "Model.h"
#include "math/vec2.h"
#include "math/vec3.h"

using std::vector;

Model::Model(const vector<vec3>& positions, const vector<vec2>& uvs, const vector<vec3>& normals, const vector<vector<int>>& indices) {
  // create attributes
  for (vec3 p : positions) this->positions.push_back(std::make_unique<Attribute>(3, p.toVector()));
  for (vec2 u : uvs)      this->uvs.push_back(std::make_unique<Attribute>(2, u.toVector()));
  for (vec3 n : normals)  this->normals.push_back(std::make_unique<Attribute>(2, n.toVector()));


  // create vertices
  for (const vector<int>& vertexAttrs : indices) {
    std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>();
    vertex->set(0, this->positions[vertexAttrs[0]].get()); // position
    vertex->set(1, this->uvs[vertexAttrs[1]].get()); // uvs
    vertex->set(2, this->normals[vertexAttrs[2]].get()); // normals

    vertices.push_back(std::move(vertex));
  }
}

vector<Vertex*> Model::getVertices() const {
  std::vector<Vertex*> rawVertices;

  for (size_t i = 0; i < vertices.size(); ++i)
    rawVertices.push_back(vertices[i].get());
  
  return rawVertices;
}
