#ifndef __ENTITIES_ENTITY_H_
#define __ENTITIES_ENTITY_H_

#include "../base/base_inc.h"
#include "../render/shader.h"
#include "../render/texture.h"
#include "../render/mesh.h"
#include "../render/model.h"

enum E_EntityTag
{
  E_ENTITY_TAG_DEFAULT = 0,
  E_ENTITY_TAG_PLAYER
};

struct E_Entity
{
  glm::vec3 pos, rot, scale;

  R_Shader* shader;
  R_Model model;

  U64 id = null, tag = E_ENTITY_TAG_DEFAULT;

  ~E_Entity();
  void Draw();
};

#endif