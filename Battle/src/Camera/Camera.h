#pragma once
#include<glm/glm.hpp>
namespace JF
{
	class Camera
	{
	public:
		Camera(size_t width, size_t height);
		~Camera() = default;
		inline const glm::mat4& get_view_projection_matrix() const { return m_ViewProjectionMatrix; }
		void set_camera_aspect(size_t width, size_t height);
		glm::vec3& get_position() { return m_Position; }
		void update_camera_matrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	private:
		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
	};
}