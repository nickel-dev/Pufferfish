#ifndef __RENDER_LIGHT_H_
#define __RENDER_LIGHT_H_

#include "../base/base_inc.h"

struct R_Light
{
  glm::vec3 pos, dir;
  glm::vec3 ambient, diffuse, specular;
};

#endif