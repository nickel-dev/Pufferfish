#ifndef __RENDER_TEXTURE_H_
#define __RENDER_TEXTURE_H_

#include "../base/base_inc.h"

struct R_Texture
{
  static void CreateErrorTexture();
  static R_Texture* GetErrorTexture();

  U32 id;

  R_Texture();
  R_Texture(const char* path);
  R_Texture(const char* path, B8 pixelated);
  void Free();
  void Load(const char* path, B8 pixelated);
  void Use();
  void UnUse();
};

struct R_CubemapTexture
{
  U32 id;

  R_CubemapTexture();
  R_CubemapTexture(const char* pRight, const char* pLeft, const char* pTop, const char* pBottom, const char* pFront, const char* pBack);
  void Free();
  void Load(const char* pRight, const char* pLeft, const char* pTop, const char* pBottom, const char* pFront, const char* pBack);
  void Use();
  void UnUse();
};

#endif