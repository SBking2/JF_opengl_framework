#pragma once
#include<memory>
#include "GLEW/glew.h"
#include "Camera/Camera.h"
#include<glm/glm.hpp>
#include"Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/EventDispatcher.h"
namespace JF
{
	class Renderer
	{
	public:
		Renderer(size_t width, size_t height);
		~Renderer();
		void on_render();
		void on_update();
		void on_event(Event& e);
		void set_camera_bound(size_t width, size_t height);
	private:
		void on_key_pressed(KeyPressedEvent& e);
	private:
		std::shared_ptr<Camera> m_Camera;
		GLuint VAO;
		GLuint VBO;
		GLuint shaderProgram;
	};
}