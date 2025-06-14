#pragma once
#include "Event.h"
namespace JF
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(size_t width, size_t height)
			:m_Width(width), m_Height(height) {}

		inline size_t get_width() const { return m_Width; }
		inline size_t get_height() const { return m_Height; }

		EventType get_event_type() const override { return EventType::WindowResize; }
		static EventType get_static_event_type() { return EventType::WindowResize; }
	private:
		size_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(size_t width, size_t height){}
		EventType get_event_type() const override { return EventType::WindowClose; }
		static EventType get_static_event_type() { return EventType::WindowClose; }
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		EventType get_event_type() const override { return EventType::AppTick; }
		static EventType get_static_event_type() { return EventType::AppTick; }
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		EventType get_event_type() const override { return EventType::AppUpdate; }
		static EventType get_static_event_type() { return EventType::AppUpdate; }
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent(){}
		EventType get_event_type() const override { return EventType::AppRender; }
		static EventType get_static_event_type() { return EventType::AppRender; }
	};
}