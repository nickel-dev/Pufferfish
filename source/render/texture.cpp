#include "texture.h"

// R_Texture
local R_Texture errorTexture;

void R_Texture::CreateErrorTexture()
{
	const U8 img[3] = {
		0xFF, 0x00, 0xFF,
	};

	glGenTextures(1, &errorTexture.id);
	glBindTexture(GL_TEXTURE_2D, errorTexture.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

R_Texture::R_Texture()
{
	return;
}

R_Texture::R_Texture(const char* path)
{
	this->Load(path, false);
}

R_Texture::R_Texture(const char* path, B8 pixelated)
{
	this->Load(path, pixelated);
}

void R_Texture::Free()
{
	if (this->id)
		glDeleteTextures(1, &this->id);
}

void R_Texture::Load(const char* path, B8 pixelated)
{
	this->Free();

	I32 w, h, bytesPerPixel;
	const U8* img = stbi_load(path, &w, &h, &bytesPerPixel, 0);
	if (!img)
		LOG_ERROR("Loading texture file failed! path: %s\n", path);

	glGenTextures(1, &this->id);
	this->Use();

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

	this->UnUse();
}

R_Texture* R_Texture::GetErrorTexture()
{
	return &errorTexture;
}

void R_Texture::Use()
{
	glEnable(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->id);
}

void R_Texture::UnUse()
{
	glDisable(GL_TEXTURE0);
	errorTexture.Use();
}

// R_CubemapTexture
R_CubemapTexture::R_CubemapTexture()
{
	return;
}

R_CubemapTexture::R_CubemapTexture(const char* pRight, const char* pLeft, const char* pTop, const char* pBottom, const char* pFront, const char* pBack)
{
	this->Load(pRight, pLeft, pTop, pBottom, pFront, pBack);
}

void R_CubemapTexture::Free()
{
	if (this->id)
		glDeleteTextures(1, &this->id);
}

void R_CubemapTexture::Load(const char* pRight, const char* pLeft, const char* pTop, const char* pBottom, const char* pFront, const char* pBack)
{
	const char* path[6] = { pRight, pLeft, pTop, pBottom, pFront, pBack };

	this->Free();
	I32 w, h, bytesPerPixel;

	glGenTextures(1, &this->id);
	this->Use();

	for (U8 i = 0; i < 6; ++i)
	{
		const U8* img = stbi_load(path[i], &w, &h, &bytesPerPixel, 0);
		LOG_ASSERT(img, "Loading cubemap texture file failed! path: %s\n", path[i]);

		I32 mode = GL_RGB;
		if (bytesPerPixel == 4)
			mode = GL_RGBA;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, img);
		stbi_image_free((void*)img);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	this->UnUse();
}

void R_CubemapTexture::Use()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
}

void R_CubemapTexture::UnUse()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, null);
}