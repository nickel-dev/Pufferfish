#ifndef __RENDER_TEXTURE_H_
#define __RENDER_TEXTURE_H_

#include "../base/base_inc.h"

struct R_Texture
{
  U32 id;

  R_Texture() {};
  R_Texture(const char* path);
  ~R_Texture();
  void Load(const char* path);
  void Use();
};

#endif