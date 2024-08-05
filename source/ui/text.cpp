#include "text.h"
#include "glm/gtc/type_ptr.hpp"

UI_Font::UI_Font()
{
  return;
}

UI_Font::UI_Font(const char* path, I32 fontSize)
{
  this->Load(path, fontSize);
}

void UI_Font::Load(const char* path, I32 fontSize)
{
  FT_Library ft;

  LOG_ASSERT(!FT_Init_FreeType(&ft), "Loading Freetype library failed!");
  LOG_ASSERT(!FT_New_Face(ft, path, 0, &this->face), "Loading Font failed! path: %s", path);

  FT_Set_Pixel_Sizes(face, 0, fontSize);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (U8 c = 0; c < 128; ++c)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      printf("Loading Glyph failed! Glyph: %c", c);
      continue;
    }

    U32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RED,
      face->glyph->bitmap.width, face->glyph->bitmap.rows,
      0, GL_RED, GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    UI_Char character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (U32)face->glyph->advance.x
    };

    chars.insert(std::pair<char, UI_Char>(c, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  // Font
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(F32) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(F32), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void UI_Font::Draw(R_Shader& s, std::string text, float x, float y, float scale, glm::vec3 color)
{
  // activate corresponding render state
  s.Use();
  glm::mat4 projection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f);
  glUniformMatrix4fv(glGetUniformLocation(s.GetProgram(), "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniform3f(glGetUniformLocation(s.GetProgram(), "uTextColor"), color.x, color.y, color.z);
  glBindVertexArray(vao);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); ++c)
  {
    UI_Char ch = this->chars[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
        // update VBO for each character
    float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos,     ypos,       0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 1.0f },

      { xpos,     ypos + h,   0.0f, 0.0f },
      { xpos + w, ypos,       1.0f, 1.0f },
      { xpos + w, ypos + h,   1.0f, 0.0f }
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.id);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}