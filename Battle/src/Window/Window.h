#pragma once

#include "Event/Event.h"

#include<string>
#include<functional>
#include<GLFW/glfw3.h>
namespace JF
{
	class Window
	{
	public:
		Window(const size_t& width, const size_t& height, const std::string& title);
		~Window();
		void on_render();
		void on_update();
		void set_viewport(size_t width, size_t height);
		void set_event_callback(const std::function<void(Event&)>& callback);
	public:
		GLFWwindow* get_glfw_window();	//»ñÈ¡glfwµÄwindow
	private:
		void bind_event();
	private:
		std::function<void(Event&)> m_EventCallback;
		GLFWwindow* m_Window;
	};
}