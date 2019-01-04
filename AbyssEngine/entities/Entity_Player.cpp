#include "Entity_Player.h"
#include "interaction/Event.h"
#include "../math/mathUtils.h"
#include "../math/vec2.h"

Entity_Player::Entity_Player(std::vector<Component*> components) : Entity(components)
{
	eventToBehaviourMap.addConnection(Event::types::PRESSDIRECTION, Behaviour::types::MOVE, false);
}

Entity_Player::~Entity_Player()
{

}

void Entity_Player::notifyKeyEvent(std::vector<KeyboardListener::KeyPress> keyPresses)
{

	vec3 directionVector(0.0f, 0.0f, 0.0f);
	unsigned int direction[] = { 0, 0, 0, 0 };

	for (size_t i = 0; i < keyPresses.size(); i++)
		if (keyPresses.at(i).action == KeyboardListener::Action::PRESSED || keyPresses.at(i).action == KeyboardListener::Action::HELD)
			switch (keyPresses.at(i).key)
			{
			case KeyBindings::Key::MOVE_UP:		// W
				directionVector += vec2(0.0f, 1.0f);
				direction[0]++;
				break;
			case KeyBindings::Key::MOVE_LEFT:	// A
				directionVector += vec2(-1.0f, 0.0f);
				direction[1]++;
				break;
			case KeyBindings::Key::MOVE_DOWN:	// S
				directionVector += vec2(0.0f, -1.0f);
				direction[2]++;
				break;
			case KeyBindings::Key::MOVE_RIGHT:	// D
				directionVector += vec2(1.0f, 0.0f);
				direction[3]++;
				break;
			}

	bool valid = direction[0] != direction[2] || direction[1] != direction[3];

	if(valid){
		directionVector.normalize();
		float angle = atan2(directionVector.y, directionVector.x);
		asyncEvents.push_back(new FloatEvent(Event::types::PRESSDIRECTION, angle));
	}
}