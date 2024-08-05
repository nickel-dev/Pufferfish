#include "texture.h"

R_Texture::R_Texture(const char* path)
{
	this->Load(path, false);
}

R_Texture::R_Texture(const char* path, B8 pixelated)
{
	this->Load(path, pixelated);
}

R_Texture::~R_Texture()
{
	glDeleteTextures(1, &this->id);
}

void R_Texture::Load(const char* path, B8 pixelated)
{
	I32 w, h, bytesPerPixel;
  const U8* img = stbi_load(path, &w, &h, &bytesPerPixel, 0);

	glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);

	I32 mode = GL_RGB;
	if (bytesPerPixel == 4)
		mode = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, img);

	if (pixelated)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free((void*)img);
}

void R_Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}