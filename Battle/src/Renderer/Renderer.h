#pragma once
#include<memory>
#include <sstream>

#include<glm/glm.hpp>
#include "GLEW/glew.h"

#include "Camera/Camera.h"
#include"Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/EventDispatcher.h"
#include "Shader/Shader.h"
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
		std::string read_file(const std::string& path);	//读取shader源文件
	private:
		std::shared_ptr<Camera> m_Camera;
		std::shared_ptr<Shader> m_Shader;
		GLuint VAO;
		GLuint VBO;
	};
}