#ifndef __ENTITIES_ENTITY_H_
#define __ENTITIES_ENTITY_H_

#include "../base/base_inc.h"

#include "../render/shader.h"
#include "../render/texture.h"
#include "../render/mesh.h"

struct E_Entity
{
    glm::vec3 pos;
    glm::vec3 rot;
    
    R_Shader* shader;
    R_Texture* texture;
    R_Mesh* mesh;

    void Draw();
};

#endif