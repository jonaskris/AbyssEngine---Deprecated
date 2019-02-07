#include "Entity_Player.h"
#include "interaction/Event.h"
#include "../math/mathUtils.h"
#include "../math/vec2.h"

namespace abyssengine {
	Entity_Player::Entity_Player(std::vector<Component*> components) : Entity(components)
	{
		eventToBehaviourMap.addConnection(Event::types::PRESSDASH, Behaviour::types::DASH, false);
		eventToBehaviourMap.addConnection(Event::types::PRESSDIRECTION, Behaviour::types::DASH, false);
		eventToBehaviourMap.addConnection(Event::types::INDASH, Behaviour::types::DASH, true);

		eventToBehaviourMap.addConnection(Event::types::PRESSDIRECTION, Behaviour::types::MOVE, false);
		eventToBehaviourMap.addConnection(Event::types::INDASH, Behaviour::types::MOVE, true);
	}

	Entity_Player::~Entity_Player()
	{

	}

	void Entity_Player::notifyKeyEvent(std::vector<KeyboardListener::KeyPress> keyPresses)
	{
		math::vec3 directionVector(0.0f, 0.0f, 0.0f);
		unsigned int direction[] = { 0, 0, 0, 0 };

		bool alreadyDashed = false;

		for (size_t i = 0; i < keyPresses.size(); i++)
			if (keyPresses.at(i).action == KeyboardListener::Action::PRESSED || keyPresses.at(i).action == KeyboardListener::Action::HELD)
				switch (keyPresses.at(i).key)
				{
				case KeyBindings::Key::MOVE_UP:		// W
					directionVector += math::vec2(0.0f, 1.0f);
					direction[0]++;
					break;
				case KeyBindings::Key::MOVE_LEFT:	// A
					directionVector += math::vec2(-1.0f, 0.0f);
					direction[1]++;
					break;
				case KeyBindings::Key::MOVE_DOWN:	// S
					directionVector += math::vec2(0.0f, -1.0f);
					direction[2]++;
					break;
				case KeyBindings::Key::MOVE_RIGHT:	// D
					directionVector += math::vec2(1.0f, 0.0f);
					direction[3]++;
					break;
				case KeyBindings::Key::DASH:		// SPACE
					if (!alreadyDashed)
					{
						asyncEvents.push_back(new Event(Event::types::PRESSDASH));
						alreadyDashed = true;
					}
					break;
				}

		bool movementValid = direction[0] != direction[2] || direction[1] != direction[3];

		if (movementValid) {
			directionVector.normalize();
			float angle = atan2(directionVector.y, directionVector.x);
			asyncEvents.push_back(new FloatEvent(Event::types::PRESSDIRECTION, angle));
		}
	}
}