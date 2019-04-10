#include "Transform.h"

using namespace Foundations;

void Transform::OnInit()
{
	m_scale = glm::vec3(1, 1, 1);
}

void Transform::Translate(glm::vec3 _value)
{
	m_position += _value;
}

void Transform::Rotate(glm::vec3 _value)
{
	m_rotation += _value;
}

void Transform::Scale(glm::vec3 _value)
{
	glm::scale(glm::mat4(1), glm::vec3(_value));
}

void Transform::SetPosition(glm::vec3 _position)
{
	m_position = _position;
}

void Transform::SetRotation(glm::vec3 _rotation)
{
	m_rotation = _rotation;
}

void Transform::SetScale(glm::vec3 _scale)
{
	m_scale = _scale;
}

glm::vec3 Transform::GetPosition()
{
	return m_position;
}

glm::vec3 Transform::GetRotation()
{
	return m_rotation;
}

glm::vec3 Transform::GetScale()
{
	return m_scale;
}