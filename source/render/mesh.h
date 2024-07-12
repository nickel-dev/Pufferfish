#ifndef __RENDER_MESH_H_
#define __RENDER_MESH_H_

#include "../base/base_inc.h"

struct R_Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;

    R_Vertex();
    R_Vertex(glm::u8vec3 pPos, glm::vec3 pNormal, glm::vec2 pTexCoord);
};

struct R_Mesh
{
    std::vector<R_Vertex> vertices;
    std::vector<U32> indices;

    U32 vao, vbo, ebo;
    U32 currIndex = 0;

    void SetupMesh();
    void Draw();
};

#endif