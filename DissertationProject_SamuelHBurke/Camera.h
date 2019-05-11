#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_CTOR_INT

#include "Component.h"
#include "Transform.h"
#include "Window.h"
#include "Input.h"
#include "AudioMaster.h"

#include "../../GLM/glm.hpp"
#include "../../GLM/gtc/matrix_transform.hpp"

namespace Foundations
{
class Camera : public Component
{
public:
	void OnInit() override;
	void OnUpdate(float _deltaTime) override;

	glm::mat4 GetProjection();
	glm::mat4 GetView();
	
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	float m_radius;
	float m_near;
	float m_far;
	glm::vec3 m_position;
	
	float m_cameraAngleX, m_cameraAngleY;

	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraLeft;


	Transform m_transform;
	Window m_window;
	Input m_input;

	AudioEngine::AudioMaster m_audio;
	
	
};
}

#endif // !CAMERA_H
