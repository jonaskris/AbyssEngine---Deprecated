#pragma once
#include "../Keybindings.h"
#include "../listeners/KeyboardListener.h"

namespace abyssengine {
	class KeyboardObserver
	{
	public:
		KeyboardObserver();
		virtual ~KeyboardObserver();
		virtual void notifyKeyEvent(const int& key, const int& scancode, const int& action, const int& mods) = 0;
	};

	class SimpleKeyboardObserver
	{
	public:
		SimpleKeyboardObserver();
		virtual ~SimpleKeyboardObserver();
		virtual void notifyKeyEvent(std::vector<KeyboardListener::KeyPress> keyPresses) = 0;
	};
}