#include "Snake.h"
#include "VertexArray.h"
#include "Texture.h"

using namespace Game;

void Snake::OnInit()
{
	m_transform = GetTransform();

	m_defaultCube = std::make_shared<Foundations::VertexArray>("../Resources/Models/cube.obj");
	m_defaultTexture = std::make_shared<Foundations::Texture>("../Resources/Textures/default.png");

	m_audio = std::make_shared<AudioEngine::AudioMaster>("../Resources/Audio/Pulsing_Hum.ogg");

	m_player.Init(m_transform);
}



void Snake::OnUpdate(float _deltaTime)
{
	m_player.Update(_deltaTime);

	glm::vec3 pos = GetPlayerPosition();
	m_audio->SetListener(-pos.x, pos.y, pos.z);

	//m_audio->SetListener(0.0f, 0, 0);
	m_audio->SetSource(0, 0, 0);

	m_audio->Play();
}

std::shared_ptr<Foundations::VertexArray> Snake::GetModel()
{
	return m_defaultCube;
}

std::shared_ptr<Foundations::Texture> Snake::GetTexture()
{
	return m_defaultTexture;
}

glm::vec3 Snake::GetPlayerPosition()
{
	return m_player.GetPlayerPosition();
}