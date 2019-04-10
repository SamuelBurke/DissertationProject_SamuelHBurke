#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_FORCE_CTOR_INT

#include <../../GLM/glm.hpp>
#include <../../GLM/gtc/matrix_transform.hpp>
#include <../../GLM/gtc/type_ptr.hpp>

#include "Component.h"

namespace Foundations
{
	class Transform : public Component
	{
	public:
		void OnInit() override;

		void Translate(glm::vec3 _value);
		void Rotate(glm::vec3 _value);
		void Scale(glm::vec3 _value);

		void SetPosition(glm::vec3 _position);
		void SetRotation(glm::vec3 _rotation);
		void SetScale(glm::vec3 _scale);
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}

#endif // !FOUNDATION_TRANSFORM_H