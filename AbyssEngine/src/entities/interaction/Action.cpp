#include "Action.h"
#include "../Entity.h"
#include "../../entities/components/PComponent.h"

namespace abyssengine {
	Action::Action(types type)
	{
		this->type = type;
	}

	void Action::executeOn(Entity* entity)
	{

	}

	Action::types Action::getType()
	{
		return type;
	}

	FloatAction::FloatAction(types type, float scalar) : Action(type)
	{
		this->scalar = scalar;
	}


	void FloatAction::executeOn(Entity* entity)
	{

	}

	VecAction::VecAction(types type, math::vec3 vector) : Action(type)
	{
		this->vector = vector;
	}

	void VecAction::executeOn(Entity* entity)
	{
		PComponent* pComponent = NULL;

		switch (type)
		{
		case SETACCELERATION:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->acceleration = vector;
			break;
		case CHANGEACCELERATION:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->acceleration += vector;
			break;
		case SETVELOCITY:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->velocity = vector;
			break;
		case CHANGEVELOCITY:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->velocity += vector;
			break;
		case SETPOSITION:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->position = vector;
			break;
		case CHANGEPOSITION:
			if ((pComponent = entity->getPComponent()) == NULL)
				return;
			pComponent->position += vector;
			break;
		default:
			std::cout << "Could not execute action: " << type << ", as code for execution in Action.h is not written" << std::endl;
			break;
		}
	}

	EventAction::EventAction(types type, Event* event) : Action(type)
	{
		this->event = event;
	}

	void EventAction::executeOn(Entity* entity)
	{
		switch (type)
		{
		case ADDEVENT:
			entity->addAsyncEvent(event);
			break;
		default:
			std::cout << "Could not execute action: " << type << ", as code for execution in Action.h is not written" << std::endl;
			break;
		}
	}
}