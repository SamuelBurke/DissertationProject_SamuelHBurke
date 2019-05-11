#include "Camera.h"
#include "AudioMaster.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <../../GLM/gtx/rotate_vector.hpp>
#include <../../GLM/gtc/quaternion.hpp>
#include <../../GLM/gtx/quaternion.hpp>

#include <iostream>

using namespace Foundations;

void Camera::OnInit()
{
	m_radius = 45.0f;
	m_near = 0.1f;
	m_far = 100.0f;

	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_cameraAngleX = 0.0f;
	m_cameraAngleY = 0.0f;

	m_transform.SetPosition(m_position);
	m_transform.SetRotation(glm::vec3(m_cameraAngleX, m_cameraAngleY, 0.0f));

	m_cameraFront = glm::vec3(0, 0, -1);
	m_cameraLeft = glm::vec3(-1, 0, 0);
	m_cameraUp = glm::vec3(0, 1, 0);

	m_projectionMatrix = glm::perspective(glm::radians(m_radius), (float)Window::GetWidth() / (float)Window::GetHeight(), m_near, m_far);
}

void Camera::OnUpdate(float _deltaTime)
{
	glm::vec3 cameraPos = m_transform.GetPosition();
	m_viewMatrix = glm::lookAt(cameraPos, cameraPos + m_cameraFront, m_cameraUp);

	m_viewMatrix = glm::translate(glm::mat4(1), m_transform.GetPosition());
	m_viewMatrix = glm::rotate(m_viewMatrix, m_cameraAngleX, glm::vec3(1, 0, 0));
	m_viewMatrix = glm::rotate(m_viewMatrix, m_cameraAngleY, glm::vec3(0, 1, 0));
	m_viewMatrix = glm::inverse(m_viewMatrix);

}

glm::mat4 Camera::GetProjection()
{
	return m_projectionMatrix;
}

glm::mat4 Camera::GetView()
{
	return m_viewMatrix;
}