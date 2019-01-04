#include <iostream>
#include "KeyboardListener.h"
#include "../observers/KeyboardObserver.h"

#define PRINTEVENTS 0

void KeyboardListener::addObserver(KeyboardObserver& observer)
{
	if (!findObserver(observer))	// Makes sure an observer is never represented more than once in the vector
		observers.push_back(&observer);
};

void KeyboardListener::addObserver(SimpleKeyboardObserver& observer)
{
	if (!findObserver(observer))	// Makes sure an observer is never represented more than once in the vector
		simpleObservers.push_back(&observer);
};

void KeyboardListener::removeObserver(KeyboardObserver& observer)
{
	for (size_t i = 0; i < observers.size(); i++)
		if (observers.at(i) == &observer) {
			observers.erase(observers.begin() + i);
			return;
		}
};

void KeyboardListener::removeObserver(SimpleKeyboardObserver& observer)
{
	for (size_t i = 0; i < simpleObservers.size(); i++)
		if (simpleObservers.at(i) == &observer) {
			simpleObservers.erase(simpleObservers.begin() + i);
			return;
		}
};

bool KeyboardListener::findObserver(KeyboardObserver& observer) {
	for (size_t i = 0; i < observers.size(); i++)
		if (observers.at(i) == &observer)
			return true;
	return false;
}

bool KeyboardListener::findObserver(SimpleKeyboardObserver& observer) {
	for (size_t i = 0; i < simpleObservers.size(); i++)
		if (simpleObservers.at(i) == &observer)
			return true;
	return false;
}

void KeyboardListener::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	#if PRINTEVENTS == 1
	std::cout << "Key: " << key << ", scancode: " << scancode << ", action: " << action << ", mods: " << mods << std::endl;
	#endif	

	switch (action)
	{
	case 0: // Released
		if (pressedKeys[KeyBindings::bindings[scancode]].pressed)
			pressedKeys[KeyBindings::bindings[scancode]].releasedThisUpdate = true;
		pressedKeys[KeyBindings::bindings[scancode]].pressed = false;
		break;
	case 1: // Pressed
		if(!pressedKeys[KeyBindings::bindings[scancode]].pressed)
			pressedKeys[KeyBindings::bindings[scancode]].pressedThisUpdate = true;
		pressedKeys[KeyBindings::bindings[scancode]].pressed = true;
		break;
	}

	for (size_t i = 0; i < observers.size(); i++)
		observers.at(i)->notifyKeyEvent(key, scancode, action, mods);
}

void KeyboardListener::update()
{
	// Find changes since last update
	std::map<KeyBindings::Key, PressedState>::iterator i;
	std::vector<KeyPress> keyPresses;


	for (i = pressedKeys.begin(); i != pressedKeys.end(); i++) {
		Action action;
		if (i->second.pressed)
			if (i->second.pressedThisUpdate)
				action = Action::PRESSED;
			else
				action = Action::HELD;
		else if (i->second.releasedThisUpdate)
			action = Action::RELEASED;
		else
			continue;
		keyPresses.push_back(KeyPress{ i->first, action });
	}

	// Notify every simpleObserver of changes
	for (size_t j = 0; j < simpleObservers.size(); j++)
		simpleObservers.at(j)->notifyKeyEvent(keyPresses);

	// Reset every pressed-/released-ThisUpdate to false
	for (i = pressedKeys.begin(); i != pressedKeys.end(); i++)
	{
		i->second.pressedThisUpdate = false;
		i->second.releasedThisUpdate = false;
	}
}