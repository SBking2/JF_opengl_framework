#pragma once
#include<glm/glm.hpp>
#include "Event/KeyEvent.h"
namespace JF
{
	class Camera
	{
	public:
		Camera(size_t width, size_t height);
		virtual ~Camera() = default;
		inline const glm::mat4& get_view_projection_matrix() const { return m_ViewProjectionMatrix; }
		void set_camera_aspect(size_t width, size_t height);
		void on_event(Event& e);
	private:
		void on_key_pressed(KeyPressedEvent& e);
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