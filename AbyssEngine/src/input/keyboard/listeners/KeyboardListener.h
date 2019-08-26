#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "../../InputEnums.h"

namespace abyssengine {
	namespace input {
		class KeyboardObserver;
		class SimpleKeyboardObserver;

		namespace KeyboardListener
		{
			struct KeyState
			{
				bool pressed = false;
				bool pressedThisUpdate = false;
				bool releasedThisUpdate = false;
			};

			static std::map<Keyboard::Key, KeyState> keyStates;

			static std::vector<KeyboardObserver*> observers;

			void addObserver(KeyboardObserver& observer);

			void removeObserver(KeyboardObserver& observer);

			void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			void update();
		}
	}
}