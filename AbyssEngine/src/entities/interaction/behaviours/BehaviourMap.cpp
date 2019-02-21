#include "BehaviourMap.h"
#include "BehaviourFactory.h"
#include "Behaviour.h"

#define getOnlyFirstEventThatMatches false

namespace abyssengine {
	BehaviourMap::BehaviourMap()
	{
		//fillPriorityList();
	};

	//BehaviourMap::BehaviourMap(const std::list<Behaviour::types>& priorityList)
	//{
	//	this->priorityList.insert(this->priorityList.begin(), priorityList.begin(), priorityList.end());
	//	fillPriorityList();
	//}

	//void BehaviourMap::fillPriorityList()
	//{
	//	for (size_t i = 0; i < Behaviour::types::MAX; i++)
	//	{
	//		bool found = false;
	//		std::list<Behaviour::types>::iterator j;
	//		for (j = priorityList.begin(); j != priorityList.end(); j++)
	//		{
	//			if ((Behaviour::types)i == *j)
	//			{
	//				found = true;
	//				break;
	//			}
	//		}
	//		if (!found) {
	//			priorityList.push_back((Behaviour::types)i);
	//		}
	//	}
	//}

	void BehaviourMap::addConnection(Event::types from, Behaviour::types to, bool negate)
	{
		bool alreadyContainsFrom = false;

		std::list<Connection>::iterator it;
		for (it = connections.begin(); it != connections.end(); it++)
		{
			if (it->from == from && it->to == to)
			{
				alreadyContainsFrom = true;
				std::cout << "Tried adding connection to set, but it or its negation is already in the set pointing to the same behavior!" << std::endl;
				break;
			}
		}

		if (!alreadyContainsFrom)
		{
			connections.push_back(Connection{ negate, from, to });
		}
	}

	std::list<Behaviour*> BehaviourMap::map(std::list<Event*>& fromList)
	{
		std::list<Behaviour*> newBehaviours;

		//std::list<Behaviour::types>::iterator i;

		for (int i = Behaviour::types::MIN + 1; i < Behaviour::types::MAX; i++)
		{
			std::list<Connection> connections;
			std::list<Connection>::iterator j;

			for (j = this->connections.begin(); j != this->connections.end(); j++)
				if (j->to == i)
					connections.push_back(*j);

			std::list<Event*> validEvents;
			for (j = connections.begin(); j != connections.end(); j++)
			{
				if (j->negate)
				{
					bool found = false;
					std::list<Event*>::iterator h;
					for (h = fromList.begin(); h != fromList.end(); h++)
					{
						if ((*h)->type == j->from)
						{
							found = true;
							goto nextBehaviour;
						}
					}
				}
				else
				{
					bool found = false;
					std::list<Event*>::iterator h;
					for (h = fromList.begin(); h != fromList.end(); h++)
					{
						if ((*h)->type == j->from)
						{
							validEvents.push_back(*h);
							found = true;
						}
					}
					if (!found)
						goto nextBehaviour;
				}
			}
			Behaviour* newBehaviour;
			newBehaviour = BehaviourFactory::newBehaviour((Behaviour::types)i, validEvents);
			if (newBehaviour != NULL)
				newBehaviours.push_back(newBehaviour);
		nextBehaviour:;
		}

		return newBehaviours;
	}
}