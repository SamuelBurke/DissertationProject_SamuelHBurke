#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <../../stb_image/stb_image.h>

using namespace Foundations;

Texture::Texture(std::string _filePath)
{
	int w = 0;
	int h = 0;
	int channels = 0;

	unsigned char *data = stbi_load(_filePath.c_str(), &w, &h, &channels, 4);

	if (!data)
	{
		throw std::exception();
	}

	m_size.x = w;
	m_size.y = h;

	glGenTextures(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 Texture::GetSize()
{
	return m_size;
}

GLuint Texture::GetID()
{
	return m_id;
}