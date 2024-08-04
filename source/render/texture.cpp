#include "texture.h"

R_Texture::R_Texture(const char* path)
{
	this->Load(path);
}

R_Texture::~R_Texture()
{
	glDeleteTextures(1, &this->id);
}

void R_Texture::Load(const char* path)
{
    SDL_Surface *img = IMG_Load(path);

	glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

	I32 mode = GL_RGB;
	if (img->format->BytesPerPixel == 4)
		mode = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SDL_FreeSurface(img);
}

void R_Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}