#include "Texture.h"
#include <SOIL/SOIL.h>
#include <iostream>


Texture::~Texture()
{
	Unload();
}

bool Texture::Load(const std::string &file)
{
	TextObj = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (TextObj == 0)
	{
		std::cout << "Texture failed to load" << SOIL_last_result() << std::endl;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, TextObj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // u axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // v axis

	return true;
}

void Texture::Unload()
{
	if (TextObj != 0)
	{
		glDeleteTextures(1, &TextObj);
		TextObj = 0;
	}

}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextObj);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}