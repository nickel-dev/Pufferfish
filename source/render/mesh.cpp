#include "mesh.h"

// R_Vertex
R_Vertex::R_Vertex() {}
R_Vertex::R_Vertex(glm::vec3 pPos, glm::vec3 pNormal, glm::vec2 pTexCoord)
{
  pos = pPos;
  normal = pNormal;
  texCoord = pTexCoord;
}

// R_Mesh
R_Mesh::R_Mesh() {}
R_Mesh::R_Mesh(std::vector<R_Vertex> pVertices, std::vector<R_Texture> pTextures, std::vector<U32> pIndices)
{
  vertices = pVertices;
  textures = pTextures;
  indices = pIndices;
  this->SetupMesh();
}

R_Mesh::~R_Mesh()
{
  glDeleteBuffers(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}

void R_Mesh::SetupMesh()
{
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(R_Vertex), &vertices[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(U32), &indices[0], GL_STATIC_DRAW);

  /// Position Vector
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(R_Vertex), NULL);

  /// Normal vector
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(R_Vertex), (void*)(sizeof(F32) * 3));

  /// UV Coordinate
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(R_Vertex), (void*)(sizeof(F32) * 6));
}

void R_Mesh::Draw()
{
  if (this->textures.size() > 0)
    this->textures[0].Use();

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glDrawElements(GL_TRIANGLES, (I32)indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}