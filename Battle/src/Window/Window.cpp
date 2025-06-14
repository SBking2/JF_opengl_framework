#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include<iostream>
namespace JF
{
	Window::Window(const size_t& width, const size_t& height, const std::string& title)
	{
		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);	//��OpenGL�뵱ǰ����
		glViewport(0, 0, width, height);	//�����ӿ�

		glfwSetWindowUserPointer(m_Window, this);	//ΪGLFW���ڹ�����ǰWindowָ�룬�Ժ��ڻص���ȡ��ʹ��

		bind_event();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::on_render()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::on_update()
	{
		glfwPollEvents();	//���������¼�
	}

	void Window::bind_event()
	{
		//���ô��ڴ�С�ص�
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				Window* window_ptr = (Window*)glfwGetWindowUserPointer(window);
				WindowResizeEvent resize_event(width, height);
				window_ptr->m_EventCallback(resize_event);
			});

		//��������ص�
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Window* window_ptr = (Window*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						window_ptr->m_EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						window_ptr->m_EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						window_ptr->m_EventCallback(event);
						break;
					}
				}
			});
	}

	void Window::set_viewport(size_t width, size_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::set_event_callback(const std::function<void(Event&)>& callback)
	{
		m_EventCallback = callback;
	}

	GLFWwindow* Window::get_glfw_window()
	{
		return m_Window;
	}
}