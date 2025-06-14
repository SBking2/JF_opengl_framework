#pragma once
#include "Event.h"
#include <functional>
namespace JF
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event)
		{

		}

		template<typename T>
		void dispatch(std::function<void(T&)> func)
		{
			if (m_Event.get_event_type() == T::get_static_event_type())
			{
				func(*dynamic_cast<T*>(&m_Event));
			}
		}

	private:
		Event& m_Event;
	};
}