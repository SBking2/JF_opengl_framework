#pragma once

#include <glm/glm.hpp>

namespace JF
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject() = default;
		glm::mat4 get_transform();	//获取物体的transform
	private:
		glm::vec3 m_Position;
		float m_Rotation;
		glm::vec2 m_Scale;
	};
}