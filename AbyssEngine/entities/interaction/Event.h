#pragma once
#include "../../math/Vec3.h"

struct Event
{
	enum types 
	{ 
		STUNNED, PRESSDASH,			// No data
		PRESSDIRECTION,				// Float
	};
	types type;

	Event(types type)
	{
		this->type = type;
	}
};

struct FloatEvent : public Event
{
	float scalar;

	FloatEvent(types type, float scalar) : Event(type)
	{
		this->scalar = scalar;
	}
};

struct Vec3Event : public Event
{
	vec3 vector;

	Vec3Event(types type, vec3 vector) : Event(type)
	{
		this->vector = vector;
	}
};