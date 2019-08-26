#include <iostream>
#include "KeyboardListener.h"
#include "../observers/KeyboardObserver.h"
#include "../../InputEnums.h"

#define PRINTEVENTS 0

namespace abyssengine {
	namespace input {
		namespace KeyboardListener {
			void addObserver(KeyboardObserver& observer)
			{
				observers.push_back(&observer);
			};

			void removeObserver(KeyboardObserver& observer)
			{
				for (size_t i = 0; i < observers.size(); i++)
					if (observers.at(i) == &observer) {
						observers.erase(observers.begin() + i);
						return;
					}
			};

			void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
			{
				Keyboard::Key keyEnum = static_cast<Keyboard::Key>(key);
				KeyState& keystate = keyStates[keyEnum];

				if (action == GLFW_PRESS) // Released
				{
					keystate.pressedThisUpdate = true;
					keystate.pressed = true;
				}
				else if (action == GLFW_RELEASE) { // Pressed
					keystate.releasedThisUpdate = true;
					keystate.pressed = false;
				}

				for (auto i = observers.begin(); i != observers.end(); i++)
					(*i)->notifyKeyEvent(static_cast<Keyboard::Key>(key), static_cast<Keyboard::Action>(action), static_cast<Keyboard::Modifier>(mods));
			}

			void update()
			{

				for (auto i = keyStates.begin(); i != keyStates.end(); i++)
				{
					KeyState keystate = (*i).second;
					if (!keystate.pressedThisUpdate && keystate.pressed)
					{
						for (auto j = observers.begin(); j != observers.end(); j++)
							(*j)->notifyKeyEvent(static_cast<Keyboard::Key>((*i).first), Keyboard::Action::HOLD, Keyboard::Modifier::NONE);
					}
				}

				// Reset every pressed-/released-ThisUpdate to false
				for (auto i = keyStates.begin(); i != keyStates.end(); i++)
				{
					i->second.pressedThisUpdate = false;
					i->second.releasedThisUpdate = false;
				}
			}
		}
	}
}