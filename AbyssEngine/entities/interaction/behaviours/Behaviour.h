#pragma once
#include <vector>
#include "../Event.h"
#include "../Action.h"

struct Behaviour
{
	enum types
	{
		MOVE, DASH, MAX
	};

	types type;
	float lifeTime;
	Behaviour(types type, float lifeTime)
	{
		this->type = type;
		this->lifeTime = lifeTime;
	}

	virtual std::list<Action*> update(float deltaTime) = 0;

	bool behaviourFinished()
	{
		return lifeTime <= 0.0f;
	}
};

struct Behaviour_MOVE : public Behaviour
{
private:
	float speed;
	float angle;
public:
	Behaviour_MOVE(float speed, FloatEvent* PRESSDIRECTIONEVENT) : Behaviour(types::MOVE, 0.0f)
	{
		this->speed = speed;
		this->angle = PRESSDIRECTIONEVENT->scalar;
	}

public:
	std::list<Action*> update(float deltaTime)
	{
		std::list<Action*> returnList;
		returnList.push_back(new VecAction(Action::types::CHANGEPOSITION, vec3(cos(angle) * speed * deltaTime, sin(angle) * speed * deltaTime, 0.0f)));

		return returnList;
	}
};

struct Behaviour_DASH : public Behaviour
{
private:
	float speed;
	float angle;
public:
	Behaviour_DASH(float time, float speed, FloatEvent* PRESSDIRECTIONEVENT) : Behaviour(types::DASH, time)
	{
		this->speed = speed;
		this->angle = PRESSDIRECTIONEVENT->scalar;
	}

public:
	std::list<Action*> update(float deltaTime)
	{
		std::list<Action*> returnList;
		returnList.push_back(new VecAction(Action::types::CHANGEPOSITION, vec3(cos(angle) * speed * deltaTime, sin(angle) * speed * deltaTime, 0.0f)));

		lifeTime -= deltaTime;
		return returnList;
	}
};