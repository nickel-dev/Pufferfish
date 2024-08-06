#ifndef __RENDER_SKYBOX_H_
#define __RENDER_SKYBOX_H_

#include "../base/base_inc.h"
#include "mesh.h"
#include "texture.h"

struct R_Skybox
{
  R_CubemapTexture texture;
  R_Mesh mesh;

  R_Skybox();
  R_Skybox(const char* dir);
  void Load(const char* dir);
};

#endif