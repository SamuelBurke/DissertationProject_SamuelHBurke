#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <../../GLM/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

namespace Foundations
{

class VertexArray;
class Texture;

struct Sampler
{
	GLint m_id;
	std::shared_ptr<Texture> m_texture;
};

class Shader
{
public:
	Shader(std::string _vertex, std::string _fragment);
	void Draw(VertexArray &_vertexArray);

	void SetUniform(std::string _uniform, glm::vec4 _value);
	void SetUniform(std::string _uniform, float _value);
	void SetUniform(std::string _uniform, glm::mat4 _value);
	void SetUniform(std::string _uniform, std::shared_ptr<Texture> _texture);

	GLuint GetID();

private:
	GLuint m_id;
	std::vector<Sampler> m_samplers;
};

}

#endif // !SHADER_H

