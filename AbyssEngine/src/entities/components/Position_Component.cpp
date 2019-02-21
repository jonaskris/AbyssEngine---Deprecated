#include "Position_Component.h"

namespace abyssengine
{
	void Position_Component::update(const float &dt)
	{
		velocity += acceleration * dt;
		position += velocity * dt;
	}

	void Position_Component::applyAction(Position_Component::VecAction& va)
	{
		switch (va.getType())
		{
		case SetPosition:
			this->position = va.getData();
			break;	
		case ChangePosition:
			this->position += va.getData();
			break;
		case SetVelocity:
			this->velocity = va.getData();
			break;
		case ChangeVelocity:
			this->velocity += va.getData();
			break;
		case SetAcceleration:
			this->acceleration = va.getData();
			break;
		case ChangeAcceleration:
			this->acceleration += va.getData();
			break;
		default:
			std::cout << "Tried applying an action to a Position_Component, but the action type was not recognized!" << std::endl;
			break;
		}
	}
}