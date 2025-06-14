#pragma once
#include "Event.h"
namespace JF
{
	class KeyEvent : public Event
	{
	public:
		inline int get_keycode()const { return m_KeyCode; }
	protected:
		KeyEvent(int keycode) :m_KeyCode(keycode) { }
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) :KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		inline int get_repeat_count() const { return m_RepeatCount; }
		EventType get_event_type() const override { return EventType::KeyPressed; }
		static EventType get_static_event_type() { return EventType::KeyPressed; }
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) :KeyEvent(keycode){}
		EventType get_event_type() const override { return EventType::KeyReleased; }
		static EventType get_static_event_type() { return EventType::KeyReleased; }
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) :KeyEvent(keycode) {}
		EventType get_event_type() const override { return EventType::KeyTyped; }
		static EventType get_static_event_type() { return EventType::KeyTyped; }
	};
}