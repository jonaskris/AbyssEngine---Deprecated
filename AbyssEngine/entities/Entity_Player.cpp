#include <vector>
#include "Entity_Player.h"
#include "components/Component.h"
#include "components/PComponent.h"

Entity_Player::Entity_Player(std::vector<Component*> components) : Entity(components)
{

}

Entity_Player::~Entity_Player()
{

}

void Entity_Player::update()
{
	if (wasdPressed[0])
	{
		this->pComponent->velocity.y = speed;
	} else if (wasdPressed[2]) {
		this->pComponent->velocity.y = -speed;
	} else {
		this->pComponent->velocity.y = 0.0f;
	}

	if (wasdPressed[3])
	{
		this->pComponent->velocity.x = speed;
	} else if (wasdPressed[1]) {
		this->pComponent->velocity.x = -speed;
	} else {
		this->pComponent->velocity.x = 0.0f;
	}

	this->pComponent->update();
}

void Entity_Player::notifyKeyEvent(const int& key, const int& scancode, const int& action, const int& mods)
{
	switch (scancode)
	{
	case 17:	 // W
		if (action == 1) {
			wasdPressed[0] = true;
		} else if (action == 0) {
			wasdPressed[0] = false;
		}
		break;
	case 30:	 // A
		if (action == 1) {
			wasdPressed[1] = true;
		}
		else if (action == 0) {
			wasdPressed[1] = false;
		}
		break;
	case 31:	 // S
		if (action == 1) {
			wasdPressed[2] = true;
		}
		else if(action == 0) {
			wasdPressed[2] = false;
		}
		break;
	case 32:	 // D
		if (action == 1) {
			wasdPressed[3] = true;
		}
		else if (action == 0) {
			wasdPressed[3] = false;
		}
		break;
	}
}