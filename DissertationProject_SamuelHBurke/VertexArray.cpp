#include "VertexArray.h"
#include "VertexBuffer.h"

#include <fstream>
#include <iostream>

using namespace Foundations;

VertexArray::VertexArray(std::string _file)
{
	m_dirty = false;
	glGenVertexArrays(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}

	m_buffers.resize(10);
	std::ifstream file(_file.c_str());

	if (!file.is_open())
	{
		throw std::exception();
	}

	std::string line;
	std::vector <std::string> splitLine;
	std::vector <glm::vec3> positions;
	std::vector <glm::vec2> texCoords;
	std::vector <glm::vec3> normals;

	std::shared_ptr<VertexBuffer> positionBuffer = NULL;
	std::shared_ptr<VertexBuffer> texCoordBuffer = NULL;
	std::shared_ptr<VertexBuffer> normalBuffer = NULL;

	while (!file.eof())
	{
		std::getline(file, line);
		if (line.length() < 1) continue;
		SplitStringWhiteSpace(line, splitLine);
		if (splitLine.size() < 1) continue;

		if (splitLine.at(0) == "v") // vertex
		{
			if (!positionBuffer)
			{
				positionBuffer = std::make_shared<VertexBuffer>();
			}

			positions.push_back(glm::vec3(
				atof(splitLine.at(1).c_str()),
				atof(splitLine.at(2).c_str()),
				atof(splitLine.at(3).c_str())));
		}

		else if (splitLine.at(0) == "vt") // vertex textures
		{
			if (!texCoordBuffer)
			{
				texCoordBuffer = std::make_shared<VertexBuffer>();
			}

			texCoords.push_back(glm::vec2(
				atof(splitLine.at(1).c_str()),
				1.0f - atof(splitLine.at(2).c_str())));
		}

		else if (splitLine.at(0) == "vn") // vertex textures
		{
			if (!normalBuffer)
			{
				normalBuffer = std::make_shared<VertexBuffer>();
			}

			normals.push_back(glm::vec3(
				atof(splitLine.at(1).c_str()),
				atof(splitLine.at(2).c_str()),
				atof(splitLine.at(3).c_str())));
		}

		else if (splitLine.at(0) == "f")
		{
			std::vector<std::string> subsplit;
			SplitString(splitLine.at(1), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }
			SplitString(splitLine.at(2), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }
			SplitString(splitLine.at(3), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }

			if (splitLine.size() < 5) continue;
			SplitString(splitLine.at(3), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }
			SplitString(splitLine.at(4), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }
			SplitString(splitLine.at(1), '/', subsplit);

			positionBuffer->Add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
			if (texCoordBuffer) { texCoordBuffer->Add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1)); }
			if (normalBuffer) { normalBuffer->Add(normals.at(atoi(subsplit.at(2).c_str()) - 1)); }
		}
	}

	SetBuffer("in_Position", positionBuffer);
	if (texCoordBuffer) { SetBuffer("in_TexCoord", texCoordBuffer); }
	if (normalBuffer) { SetBuffer("in_Normal", normalBuffer); }
}

VertexArray::VertexArray() : m_dirty(false)
{
	glGenVertexArrays(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}

	m_buffers.resize(10);
}

void VertexArray::SplitStringWhiteSpace(std::string& _input, std::vector<std::string>& _output)
{
	std::string curr;
	_output.clear();

	for (size_t i = 0; i < _input.length(); i++)
	{
		if (_input.at(i) == ' ' ||
			_input.at(i) == '\r' ||
			_input.at(i) == '\n' ||
			_input.at(i) == '\t')
		{
			if (curr.length() > 0)
			{
				_output.push_back(curr);
				curr = "";
			}
		}

		else
		{
			curr += _input.at(i);
		}
	}

	if (curr.length() > 0)
	{
		_output.push_back(curr);
	}
}

void VertexArray::SplitString(std::string& _input, char _splitter, std::vector<std::string>& _output)
{
	std::string curr;
	_output.clear();

	for (size_t i = 0; i < _input.length(); i++)
	{
		if (_input.at(i) == _splitter)
		{
			_output.push_back(curr);
			curr = "";
		}
		else
		{
			curr += _input.at(i);
		}
	}

	if (curr.length() > 0)
	{
		_output.push_back(curr);
	}
}

void VertexArray::SetBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer)
{
	if (_attribute == "in_Position")
	{
		m_buffers.at(0) = _buffer;
	}

	else if (_attribute == "in_Color")
	{
		m_buffers.at(1) = _buffer;
	}

	else if (_attribute == "in_TexCoord")
	{
		m_buffers.at(2) = _buffer;
	}

	else if (_attribute == "in_Normal")
	{
		m_buffers.at(3) = _buffer;
	}

	else
	{
		throw std::exception();
	}

	m_dirty = true;
}

int VertexArray::GetVertexCount()
{
	if (!m_buffers.at(0))
	{
		throw std::exception();
	}

	return m_buffers.at(0)->GetDataSize() / m_buffers.at(0)->GetComponents();
}

GLuint VertexArray::GetID()
{
	if (m_dirty)
	{
		glBindVertexArray(m_id);

		for (size_t i = 0; i < m_buffers.size(); i++)
		{
			if (m_buffers.at(i))
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_buffers.at(i)->GetID());

				glVertexAttribPointer(i, m_buffers.at(i)->GetComponents(), GL_FLOAT, GL_FALSE,
					m_buffers.at(i)->GetComponents() * sizeof(GLfloat), (void *)0);

				glEnableVertexAttribArray(i);
			}

			else
			{
				glDisableVertexAttribArray(i);
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		m_dirty = false;
	}

	return m_id;
}