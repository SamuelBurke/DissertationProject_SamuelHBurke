#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include <../../GLM/glm.hpp>
#include <vector>
#include <string>
#include <memory>

namespace Foundations
{
class VertexBuffer;

class VertexArray
{
public:
	VertexArray();
	VertexArray(std::string _file);

	void SetBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer);
	int GetVertexCount();
	GLuint GetID();

private:
	void SplitStringWhiteSpace(std::string &_input, std::vector<std::string> &_output);
	void SplitString(std::string &_input, char _splitter, std::vector <std::string> &_output);

	GLuint m_id;
	bool m_dirty;
	std::vector <std::shared_ptr<VertexBuffer>> m_buffers;

};
}

#endif // !VERTEXARRAY_H
