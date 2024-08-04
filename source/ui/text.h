#ifndef __UI_TEXT_H_
#define __UI_TEXT_H_

#include "../base/base_inc.h"
#include "../render/shader.h"

struct UI_Char
{
  U32 id;
  glm::ivec2 size;
  glm::ivec2 bearing;
  U32 advance;
};

struct UI_Font
{
  FT_Face face;
  std::unordered_map<char, UI_Char> chars;
  U32 vao, vbo;

  UI_Font();
  UI_Font(const char* path, I32 fontSize);
  void Load(const char* path, I32 fontSize);
  void Draw(R_Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif