#ifndef __ENTITIES_ENTITY_H_
#define __ENTITIES_ENTITY_H_

#include "../base/base_inc.h"

#include "../render/shader.h"
#include "../render/texture.h"
#include "../render/mesh.h"
#include <unordered_map>

enum E_EntityTag
{
  E_ENTITY_TAG_DEFAULT = 0,
  E_ENTITY_TAG_PLAYER
};

struct E_Entity
{
  glm::vec3 pos, rot;

  R_Shader* shader;
  R_Texture* texture;
  R_Mesh* mesh;

  U64 tag = E_ENTITY_TAG_DEFAULT;
  std::string name = "Entity";

  void Draw();
};

#endif