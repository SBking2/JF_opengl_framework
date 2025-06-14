#include "Application.h"
#include<iostream>
#include<cassert>
namespace JF
{
	Application::Application()
	{
		m_Width = 800;
		m_Height = 600;

		glfw_init();
		m_Window = std::make_shared<Window>(m_Width, m_Height, "My Window");
		glew_init();
		m_Renderer = std::make_shared<Renderer>(m_Width, m_Height);

		//��on_eventע����GLFW�Ļص���
		m_Window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
	}

	void Application::on_render()
	{
		m_Renderer->on_render();
		m_Window->on_render();	//Window��Ⱦ��Ҫ����Renderer���棬SwapBuffer�����Ⱦ��������ʾ��Window��
	}

	void Application::on_update()
	{
		m_Renderer->on_update();
		m_Window->on_update();
	}

	void Application::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::on_window_resize, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::on_key_pressed, this, std::placeholders::_1));

		m_Renderer->on_event(e);
	}

	std::shared_ptr<Window> Application::get_window() { return m_Window; }
	std::shared_ptr<Renderer> Application::get_renderer() { return m_Renderer; }

	void Application::glfw_init()
	{
		if (!glfwInit())
		{
			std::cerr << "============= GLFW ��ʼ��ʧ��! =============" << std::endl;
			assert(true);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //���汾��
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //�ΰ汾��
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //ʹ�ú���ģʽ
	}

	/// <summary>
	/// glew��ʼ������Ҫ����glfwMakeContextCurrent()����
	/// </summary>
	void Application::glew_init()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cerr << "============= GLEW ��ʼ��ʧ��! =============" << std::endl;
			assert(true);
		}
	}

	void Application::on_window_resize(WindowResizeEvent& e)
	{
		m_Window->set_viewport(e.get_width(), e.get_height());
		m_Renderer->set_camera_bound(e.get_width(), e.get_height());
		std::cout << "Window Resize Width: " << e.get_width() << " Height: " << e.get_height() << std::endl;
	}
	void Application::on_window_close(WindowCloseEvent& e)
	{
		std::cout << "Window Close!" << std::endl;
	}
	void Application::on_key_pressed(KeyPressedEvent& e)
	{
		if (e.get_repeat_count() > 0)
			return;

		std::cout << "Key Pressed :" << e.get_keycode() << std::endl;
	}
}