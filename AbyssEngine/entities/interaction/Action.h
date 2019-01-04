#pragma once
#include <iostream>
#include "../../math/vec3.h"

class Entity;

struct Action
{
	enum types 
	{
												// No data
												// Float
		SETACCELERATION, CHANGEACCELERATION,	// Vec3
		SETVELOCITY, CHANGEVELOCITY,
		SETPOSITION, CHANGEPOSITION
	};

	types type;

	Action(types type);

	virtual void executeOn(Entity* entity);

	types getType();
};

struct FloatAction : public Action
{
	float scalar;

	FloatAction(types type, float scalar);

	void executeOn(Entity* entity);
};

struct VecAction : public Action
{
	vec3 vector;

	VecAction(types type, vec3 vector);

	void executeOn(Entity* entity);
};