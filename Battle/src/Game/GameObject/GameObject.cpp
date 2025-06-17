#include "GameObject.h"
#include<glm/gtc/matrix_transform.hpp>
namespace JF
{
	GameObject::GameObject():m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
	{
		
	}

	glm::mat4 GameObject::get_transform()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
			* glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1))
			* glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, 1.0f));

		return transform;
	}
}