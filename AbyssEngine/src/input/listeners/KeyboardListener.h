#pragma once
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Keybindings.h"

namespace abyssengine {
	class KeyboardObserver;
	class SimpleKeyboardObserver;

	namespace KeyboardListener
	{
		enum Action
		{
			RELEASED, PRESSED, HELD
		};

		struct KeyPress
		{
			KeyBindings::Key key;
			Action action;
		};

		struct PressedState
		{
			bool pressed;
			bool pressedThisUpdate;
			bool releasedThisUpdate;
		};

		static std::map<KeyBindings::Key, PressedState> pressedKeys;

		static std::vector<KeyboardObserver*> observers;
		static std::vector<SimpleKeyboardObserver*> simpleObservers;

		void addObserver(KeyboardObserver& observer);
		void addObserver(SimpleKeyboardObserver& observer);

		void removeObserver(KeyboardObserver& observer);
		void removeObserver(SimpleKeyboardObserver& observer);

		bool findObserver(KeyboardObserver& observer);
		bool findObserver(SimpleKeyboardObserver& observer);

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void update();
	}
}