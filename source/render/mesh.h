#ifndef __RENDER_MESH_H_
#define __RENDER_MESH_H_

#include "../base/base_inc.h"
#include "texture.h"

struct R_Vertex
{
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec2 texCoord;

  R_Vertex();
  R_Vertex(glm::vec3 pPos, glm::vec3 pNormal, glm::vec2 pTexCoord);
};

struct R_Mesh
{
  std::vector<R_Vertex> vertices;
  std::vector<R_Texture> textures;
  std::vector<U32> indices;
  U32 vao, vbo, ebo;

	R_Mesh();
  R_Mesh(std::vector<R_Vertex> pVertices, std::vector<R_Texture> pTextures, std::vector<U32> pIndices);
  ~R_Mesh();
  void SetupMesh();
  void Draw();
};

#endif