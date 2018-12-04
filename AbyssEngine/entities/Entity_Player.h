#pragma once
#include "Entity.h"
#include "../input/observers/KeyboardObserver.h"

class Entity_Player : public Entity, KeyboardObserver
{
private:
	float speed = 1.0f;
	bool wasdPressed[4] = {false, false, false, false};
public:
	Entity_Player(std::vector<Component*> components);
	~Entity_Player();

	void update();
	void notifyKeyEvent(const int& key, const int& scancode, const int& action, const int& mods);
};