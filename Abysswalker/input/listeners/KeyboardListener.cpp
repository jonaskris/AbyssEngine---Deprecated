#include <iostream>
#include "KeyboardListener.h"
#include "../observers/KeyboardObserver.h"

void KeyboardListener::addObserver(KeyboardObserver& observer)
{
	if (!findObserver(observer)) { // Makes sure an observer is never represented more than once in the vector
		observers.push_back(&observer);
	}
};
void KeyboardListener::removeObserver(KeyboardObserver& observer)
{
	for (size_t i = 0; i < observers.size(); i++) {
		if (observers.at(i) == &observer) {
			observers.erase(observers.begin() + i);
			return;
		}
	}
};

bool KeyboardListener::findObserver(KeyboardObserver& observer) {
	for (size_t i = 0; i < observers.size(); i++) {
		if (observers.at(i) == &observer) {
			return true;
		}
	}
	return false;
}

int KeyboardListener::getObserversSize() {
	return observers.size();
}

void KeyboardListener::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key: " << key << ", scancode: " << scancode << ", action: " << action << ", mods: " << mods << std::endl;
	for (size_t i = 0; i < observers.size(); i++) {
		observers.at(i)->notifyKeyEvent(key, scancode, action, mods);
	}
}