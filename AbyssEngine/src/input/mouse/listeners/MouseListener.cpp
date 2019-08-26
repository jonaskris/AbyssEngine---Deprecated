#include <iostream>
#include "MouseListener.h"
#include "../observers/MouseObserver.h"

namespace abyssengine {
	namespace input {
		namespace MouseListener {
			void MouseListener::addObserver(MouseObserver& observer, MouseListenerType type)
			{
				observers[type].push_back(&observer);
			};

			void MouseListener::removeObserver(MouseObserver& observer, MouseListenerType type)
			{
				for (size_t i = 0; i < observers[type].size(); i++)
					if (observers[type].at(i) == &observer) {
						observers[type].erase(observers[type].begin() + i);
						return;
					}
			};

			void mouse_position_callback(GLFWwindow * window, double xpos, double ypos)
			{
				
				for (size_t i = 0; i < observers[POSITION].size(); i++)
					observers[POSITION].at(i)->notifyMousePositionEvent(math::vec2f((float)xpos, (float)ypos), lastPosition);
				lastPosition = math::vec2f{ (float)xpos, (float)ypos };
			}

			void mouse_enter_callback(GLFWwindow * window, int entered)
			{
				for (size_t i = 0; i < observers[ENTER].size(); i++)
					observers[ENTER].at(i)->notifyMouseEnterEvent((entered == 1) ? (Mouse::Action::ENTER) : (Mouse::Action::EXIT), lastPosition);
			}

			void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
			{
				for (size_t i = 0; i < observers[BUTTON].size(); i++)
					observers[BUTTON].at(i)->notifyMouseButtonEvent(static_cast<Mouse::Button>(button), static_cast<Mouse::Action>(action), static_cast<Mouse::Modifier>(mods), lastPosition);
			}

			void mouse_scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
			{
				for (size_t i = 0; i < observers[SCROLL].size(); i++)
					observers[SCROLL].at(i)->notifyMouseScrollEvent(math::vec2f{ (float)xoffset, (float)yoffset });
			}

			void update()
			{
				for (auto it = buttonStates.begin(); it != buttonStates.end(); it++)
				{
					ButtonState buttonState = (*it).second;
					if (!buttonState.pressedThisUpdate && buttonState.pressed)
					{
						for (auto jt = observers[MouseListenerType::BUTTON].begin(); jt != observers[MouseListenerType::BUTTON].end(); jt++)
							(*jt)->notifyMouseButtonEvent(static_cast<Mouse::Button>((*it).first), Mouse::Action::HOLD, Mouse::Modifier::NONE, lastPosition);
					}
				}

				for (auto it = buttonStates.begin(); it != buttonStates.end(); it++)
				{
					(*it).second.pressedThisUpdate = false;
					(*it).second.releasedThisUpdate = false;
				}
			}
		}
	}
}