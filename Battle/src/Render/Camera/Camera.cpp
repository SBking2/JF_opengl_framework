#include "Camera.h"
#include "Event/EventDispatcher.h"

#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
namespace JF
{
	Camera::Camera(size_t width, size_t height)
	{
		float aspect = (float)width / (float)height;
		m_ProjectionMatrix = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::set_camera_aspect(size_t width, size_t height)
	{
		float aspect = (float)width / (float)height;
		m_ProjectionMatrix = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
		update_camera_matrix();
	}

	void Camera::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Camera::on_key_pressed, this, std::placeholders::_1));
	}

	void Camera::on_key_pressed(KeyPressedEvent& e)
	{
		float speed = 0.01;

		if (e.get_keycode() == GLFW_KEY_UP)
			m_Position.y += speed;

		if (e.get_keycode() == GLFW_KEY_DOWN)
			m_Position.y -= speed;

		if (e.get_keycode() == GLFW_KEY_RIGHT)
			m_Position.x += speed;

		if (e.get_keycode() == GLFW_KEY_LEFT)
			m_Position.x -= speed;

		if (e.get_keycode() == GLFW_KEY_W)
			m_Rotation += speed;

		if (e.get_keycode() == GLFW_KEY_S)
			m_Rotation -= speed;

		update_camera_matrix();
	}

	void Camera::update_camera_matrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
			* glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}