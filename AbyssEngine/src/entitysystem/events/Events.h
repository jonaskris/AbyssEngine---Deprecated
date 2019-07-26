#pragma once
#include "Event.h"

namespace entitysystem
{
	/*
		Event used for testing purposes.
	*/
	struct EventA : public Event<EventA>
	{
		bool b;
		EventA(bool b, const float& lifetime) : Event(lifetime), b(b) {};
	};

	/*
		TargetedEvent used for testing purposes.
	*/
	struct EventB : public TargetedEvent<EventB>
	{
		bool b;
		EventB(const float& lifetime, bool b) : TargetedEvent(lifetime), b(b) {};
		EventB(const size_t& entityId, const float& lifetime, bool b) : TargetedEvent(entityId, lifetime), b(b) {};
	};
}