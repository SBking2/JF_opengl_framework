#include "Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include<iostream>
namespace JF
{
	Window::Window(const size_t& width, const size_t& height, const std::string& title)
	{
		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);	//绑定OpenGL与当前窗口
		glViewport(0, 0, width, height);	//设置视口

		glfwSetWindowUserPointer(m_Window, this);	//为GLFW窗口关联当前Window指针，以后在回调中取出使用

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
		glfwPollEvents();	//处理输入事件
	}

	void Window::bind_event()
	{
		//设置窗口大小回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				Window* window_ptr = (Window*)glfwGetWindowUserPointer(window);
				WindowResizeEvent resize_event(width, height);
				window_ptr->m_EventCallback(resize_event);
			});

		//键盘输入回调
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