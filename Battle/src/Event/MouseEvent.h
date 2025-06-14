#pragma once
#include "Event.h"
namespace JF
{
	/// <summary>
	/// 鼠标移动事件
	/// </summary>
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) :m_MouseX(x), m_MouseY(y) {}
		inline float get_x() const { return m_MouseX; }
		inline float get_y() const { return m_MouseY; }
		EventType get_event_type() const override { return EventType::MouseMoved; }
		static EventType get_static_event_type() { return EventType::MouseMoved; }
	private:
		float m_MouseX, m_MouseY;
	};

	/// <summary>
	/// 鼠标滚轮事件
	/// </summary>
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetX, float offsetY) :m_OffsetX(offsetX), m_OffsetY(offsetY) {}
		inline float get_offset_x() const { return m_OffsetX; }
		inline float get_offset_y() const { return m_OffsetY; }
		EventType get_event_type() const override { return EventType::MouseScrolled; }
		static EventType get_static_event_type() { return EventType::MouseScrolled; }
	private:
		float m_OffsetX, m_OffsetY;
	};

#pragma region 鼠标按键
	class MouseButtonEvent : public Event
	{
	public:
		inline int get_button() const { return m_Button; }
	protected:
		MouseButtonEvent(int button) :m_Button(button) {}
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		EventType get_event_type() const override { return EventType::MouseButtonPressed; }
		static EventType get_static_event_type() { return EventType::MouseButtonPressed; }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		EventType get_event_type() const override { return EventType::MouseButtonReleased; }
		static EventType get_static_event_type() { return EventType::MouseButtonReleased; }
	};
#pragma endregion

}