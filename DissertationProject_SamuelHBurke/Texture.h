#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <../../GLM/glm.hpp>
#include <string>

namespace Foundations
{

class Texture
{
public:
	Texture(std::string _filePath);

	glm::vec2 GetSize();
	GLuint GetID();

private:
	GLuint m_id;
	glm::vec2 m_size;
};

}
#endif // !TEXTURE_H
