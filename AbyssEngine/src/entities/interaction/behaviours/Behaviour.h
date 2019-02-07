#pragma once
#include <vector>
#include "../Event.h"
#include "../Action.h"

namespace abyssengine {
	struct Behaviour
	{
		enum types
		{
			MOVE, DASH, MAX
		};

		types type;
		double lifeTime;
		Behaviour(types type, double lifeTime)
		{
			this->type = type;
			this->lifeTime = lifeTime;
		}

		virtual std::list<Action*> update(double deltaTime) = 0;

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
		std::list<Action*> update(double deltaTime)
		{
			std::list<Action*> returnList;
			returnList.push_back(new VecAction(Action::types::CHANGEPOSITION, math::vec3(cos(angle) * speed * (float)deltaTime, sin(angle) * speed * (float)deltaTime, 0.0f)));

			return returnList;
		}
	};

	struct Behaviour_DASH : public Behaviour
	{
	private:
		float speed;
		float angle;
	public:
		Behaviour_DASH(double time, float speed, FloatEvent* PRESSDIRECTIONEVENT) : Behaviour(types::DASH, time)
		{
			this->speed = speed;
			this->angle = PRESSDIRECTIONEVENT->scalar;
		}

	public:
		std::list<Action*> update(double deltaTime)
		{
			deltaTime = ((lifeTime < deltaTime) ? lifeTime : deltaTime);

			std::list<Action*> returnList;
			returnList.push_back(new VecAction(Action::types::CHANGEPOSITION, math::vec3(cos(angle) * speed * (float)deltaTime, sin(angle) * speed * (float)deltaTime, 0.0f)));
			returnList.push_back(new EventAction(Action::types::ADDEVENT, new Event(Event::types::INDASH)));

			lifeTime -= deltaTime;
			return returnList;
		}
	};
}