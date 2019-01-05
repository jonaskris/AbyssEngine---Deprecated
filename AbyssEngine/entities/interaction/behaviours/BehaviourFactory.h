#pragma once
#include <list>
#include "Behaviour.h"
#include "../Event.h"
#include "../../../math/vec3.h"

namespace BehaviourFactory
{
	Behaviour* newBehaviour(Behaviour::types type, std::list<Event*> events)
	{
		FloatEvent* directionEvent = NULL;
		std::list<Event*>::iterator eventsIterator;

		switch (type)
		{
		case Behaviour::types::MOVE:
			for (eventsIterator = events.begin(); eventsIterator != events.end(); eventsIterator++)
			{
				if ((*eventsIterator)->type == Event::types::PRESSDIRECTION)
				{
					directionEvent = (FloatEvent*)(*eventsIterator);
					break;
				}
			}

			if (directionEvent != NULL)
				return new Behaviour_MOVE(80.0, directionEvent);

			break;
		case Behaviour::types::DASH:
			for (eventsIterator = events.begin(); eventsIterator != events.end(); eventsIterator++)
			{
				if ((*eventsIterator)->type == Event::types::PRESSDIRECTION)
				{
					directionEvent = (FloatEvent*)(*eventsIterator);
					break;
				}
			}
			if(directionEvent != NULL)
				return new Behaviour_DASH(0.07, 300.0f, directionEvent);

			break;
		}
		return NULL;
	}


};