#include "../base/base_inc.h"
#include "mesh.h"

R_Vertex::R_Vertex() {}
R_Vertex::R_Vertex(glm::u8vec3 pPos, glm::vec3 pNormal, glm::vec2 pTexCoord)
{
  pos = pPos;
  normal = pNormal;
  texCoord = pTexCoord;
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
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  /// Position Vector
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(R_Vertex), NULL);

  /// Normal vector
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(R_Vertex), (void*)(sizeof(F32) * 3));

  /// UV Coordinate
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(R_Vertex), (void*)(sizeof(F32) * 6));
}

void R_Mesh::Draw()
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glDrawElements(GL_TRIANGLES, (U32)indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}