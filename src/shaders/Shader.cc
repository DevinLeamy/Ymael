#include "shaders/Shader.h"

#include <memory>
#include <vector>

#include "VertexArrayObject.h"

void Shader::run(VertexArrayObject* inStream, VertexArrayObject* outStream, std::vector<int> attrIndices) {
  // runs the shader with the indices of the attributes of the vertex, in the instream
  // eg: positions = positions[attrIndices[0]], rotation = rotations[attrIndices[1]]
}
void Shader::run(VertexArrayObject* inStream, VertexArrayObject* outStream, int vertexIndex) {
  // runs the shader with the index of the vertex
  // eg: position = positions[vertexIndex], rotation = rotations[vertexIndex]
}
