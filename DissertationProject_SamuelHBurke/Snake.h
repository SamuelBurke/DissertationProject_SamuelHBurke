#ifndef SNAKE_H
#define SNAKE_H

#include "Component.h"
#include "Player.h"
#include "AudioMaster.h"

#include <memory>
#include <../../GLM/glm.hpp>

class Foundations::VertexArray;
class Foundations::Texture;
class Foundations::Transform;

namespace Game
{

class Snake : public Foundations::Component
{
public:
	void OnInit() override;
	void OnUpdate(float _deltaTime) override;

	std::shared_ptr<Foundations::VertexArray> GetModel();
	std::shared_ptr<Foundations::Texture> GetTexture();

	glm::vec3 GetPlayerPosition();

private:
	Player m_player;

	std::shared_ptr<Foundations::VertexArray> m_defaultCube;
	std::shared_ptr<Foundations::Texture> m_defaultTexture;
	std::shared_ptr<Foundations::Transform> m_transform;

	std::shared_ptr<AudioEngine::AudioMaster> m_audio;

};

}
#endif // !SNAKE_H
