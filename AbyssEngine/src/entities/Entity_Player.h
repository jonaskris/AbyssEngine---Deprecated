#pragma once
#include <vector>
#include "Entity.h"
#include "../input/listeners/KeyboardListener.h"
#include "../input/observers/KeyboardObserver.h"

namespace abyssengine {
	class Entity_Player : public Entity, SimpleKeyboardObserver
	{
	public:
		Entity_Player(std::vector<Component*> components);
		~Entity_Player();

		void notifyKeyEvent(std::vector<KeyboardListener::KeyPress> keyPresses);
	};
}