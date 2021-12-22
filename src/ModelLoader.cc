#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <memory>

#include "ModelLoader.h"
#include "math/vec3.h"
#include "math/vec2.h"
#include "Model.h"

vec2 getVec2(std::istringstream& lineStream) {
  vec2 res;
  lineStream >> res.x >> res.y;

  return res;
}

vec3 getVec3(std::istringstream& lineStream) {
  vec3 res;
  lineStream >> res.x >> res.y >> res.z;

  return res;
}

std::vector<std::string> split(std::string s, char c) {
  std::vector<std::string> res;

  std::string segment = "";
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] == c) {
      if (segment != "")
        res.push_back(segment);
      segment = "";
    } else {
      segment += s[i];
    }
  }
  if (segment != "")
    res.push_back(segment);
  
  return res;
}

std::vector<int> parseFaceVertexIndices(std::string indices) {
  std::vector<int> res;
  std::vector<std::string> sIndices = split(indices, '/');

  for (std::string index : sIndices)
    res.push_back(std::stoi(index));

  return res;
}
std::vector<std::vector<int>> getFaceIndices(std::istringstream& lineStream) {
  std::vector<std::vector<int>> res(3);

  std::string v1, v2, v3;
  res[0] = parseFaceVertexIndices(v1);
  res[1] = parseFaceVertexIndices(v2);
  res[2] = parseFaceVertexIndices(v3);

  return res;
}

vec2 getUV(std::istringstream& lineStream) {
  return getVec2(lineStream);
}

vec3 getVertexPosition(std::istringstream &lineStream) {
  return getVec3(lineStream);
}

vec3 getNormal(std::istringstream &lineStream) {
  return getVec3(lineStream);
}

std::unique_ptr<Model> loadModel(std::string modelPath) {
  std::vector<vec3> vertices; // positions
  std::vector<vec2> uvs;      // texture coords
  std::vector<vec3> normals;  // vertex normals
  std::vector<std::vector<int>> indices; // indices

  std::ifstream modelFile(modelPath.data());

  if (!modelFile) {
    std::cout << "Error: unable to read model file - " + modelPath;
    exit(1);
  }

  std::string line, type;

  while (std::getline(modelFile, line)) {
    std::cout << line << std::endl;
    std::istringstream lineStream(line);

    lineStream >> type;

    if (type == "v")
      vertices.push_back(getVertexPosition(lineStream));
    else if (type == "vt")
      uvs.push_back(getUV(lineStream));
    else if (type == "vn")
      normals.push_back(getNormal(lineStream));
    else if (type == "f")
      indices.emplace_back(getFaceIndices(lineStream));
  }

  return std::make_unique<Model>(vertices, uvs, normals, indices);
}
