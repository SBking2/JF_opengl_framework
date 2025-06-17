#pragma once
#include<memory>
#include "Render/Renderer/Renderer.h"
#include "Window/Window.h"

#include "Event/EventDispatcher.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
namespace JF
{
	/// <summary>
	/// 管理窗口与渲染器
	/// </summary>
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
		void on_render();
		void on_update();
		void on_event(Event& e);
	public:
		std::shared_ptr<Window> get_window();
		std::shared_ptr<Renderer> get_renderer();
	private:
		void glfw_init();
		void glew_init();
		void on_window_resize(WindowResizeEvent& e);
		void on_window_close(WindowCloseEvent& e);
		void on_key_pressed(KeyPressedEvent& e);
	private:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<Renderer> m_Renderer;
		size_t m_Width, m_Height;
	};
}