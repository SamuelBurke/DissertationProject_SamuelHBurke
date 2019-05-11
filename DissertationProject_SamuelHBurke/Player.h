#ifndef PLAYER_H
#define PLAYER_H

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "Component.h"

#include "Transform.h"
#include "Input.h"

#include <memory>
#include <../../GLM/ext.hpp>

namespace Game
{
class Player
{
public:
	void Init(std::shared_ptr<Foundations::Transform> _transform);
	void Update(float _deltaTime);
	glm::vec3 GetPlayerPosition();

private:
	float m_speed;
	glm::vec3 m_direction;
	glm::vec3 m_playerPos;

	std::shared_ptr<Foundations::Transform> m_transform;

	Foundations::Input m_input;
};
}

#endif // !PLAYER_H
