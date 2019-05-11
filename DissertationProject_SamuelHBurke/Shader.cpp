#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

#include <../../GLM/ext.hpp>
#include <iostream>
#include <fstream>

using namespace Foundations;

Shader::Shader(std::string _vertex, std::string _fragment)
{
	std::ifstream file(_vertex.c_str());
	std::string vertexSource;

	if (!file.is_open())
	{
		throw std::exception();
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		vertexSource += line + "\n";
	}

	file.close();
	file.open(_fragment.c_str());
	std::string fragmentSource;

	if (!file.is_open())
	{
		throw std::exception();
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		fragmentSource += line + "\n";
	}

	const GLchar *vertexShader = vertexSource.c_str();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);
	GLint success = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	const GLchar *fragmentShader = fragmentSource.c_str();
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShaderID);
	glAttachShader(m_id, fragmentShaderID);
	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_Color");
	glBindAttribLocation(m_id, 2, "in_TexCoord");
	glBindAttribLocation(m_id, 3, "in_Normal");

	if (glGetError() != GL_NO_ERROR)
	{
		throw std::exception();
	}

	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	glDetachShader(m_id, vertexShaderID);
	glDeleteShader(vertexShaderID);
	glDetachShader(m_id, fragmentShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::Draw(VertexArray& _vertexArray)
{
	glUseProgram(m_id);
	glBindVertexArray(_vertexArray.GetID());

	for (size_t i = 0; i < m_samplers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		if (m_samplers.at(i).m_texture)
		{
			glBindTexture(GL_TEXTURE_2D, m_samplers.at(i).m_texture->GetID());
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, _vertexArray.GetVertexCount());

	for (size_t i = 0; i < m_samplers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void Shader::SetUniform(std::string _uniform, glm::vec4 _value)
{
	GLuint uniformID = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformID == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform4f(uniformID, _value.x, _value.y, _value.z, _value.w);
	glUseProgram(0);
}

void Shader::SetUniform(std::string _uniform, float _value)
{
	GLuint uniformID = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformID == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform1f(uniformID, _value);
	glUseProgram(0);
}

void Shader::SetUniform(std::string _uniform, glm::mat4 _value)
{
	GLuint uniformID = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformID == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

void Shader::SetUniform(std::string _uniform, std::shared_ptr<Texture> _texture)
{
	GLuint uniformID = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformID == -1)
	{
		throw std::exception();
	}

	for (size_t i = 0; i < m_samplers.size(); i++)
	{
		if (m_samplers.at(i).m_id == uniformID)
		{
			m_samplers.at(i).m_texture = _texture;

			glUseProgram(m_id);
			glUniform1i(uniformID, i);
			glUseProgram(0);
			return;
		}
	}

	Sampler samp;
	samp.m_id = uniformID;
	samp.m_texture = _texture;
	m_samplers.push_back(samp);

	glUseProgram(m_id);
	glUniform1i(uniformID, m_samplers.size() - 1);
	glUseProgram(0);
}

GLuint Shader::GetID()
{
	return m_id;
}