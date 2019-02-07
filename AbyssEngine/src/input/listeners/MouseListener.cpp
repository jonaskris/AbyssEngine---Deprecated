#include <iostream>
#include "MouseListener.h"
#include "../observers/MousePositionObserver.h"

#define PRINTEVENTS 0

namespace abyssengine {
	void MouseListener::addObserver(MouseObserver& observer, MouseListenerType type)
	{
		if (!findObserver(observer, type)) { // Makes sure an observer is never represented more than once in the vector
			observers[type].push_back(&observer);
		}
	};

	void MouseListener::removeObserver(MouseObserver& observer, MouseListenerType type)
	{
		for (size_t i = 0; i < observers[type].size(); i++) {
			if (observers[type].at(i) == &observer) {
				observers[type].erase(observers[type].begin() + i);
				return;
			}
		}
	};

	bool MouseListener::findObserver(MouseObserver& observer, MouseListenerType type)
	{
		for (size_t i = 0; i < observers[type].size(); i++) {
			if (observers[type].at(i) == &observer) {
				return true;
			}
		}
		return false;
	}

	int MouseListener::getObserversSize() {
		int returnValue = 0;
		for (size_t i = 0; i < observers->size(); i++) {
			returnValue += getObserversSize(MouseListenerType(i));
		}
		return returnValue;
	}

	int MouseListener::getObserversSize(MouseListenerType type) {
		return observers[type].size();
	}

	void MouseListener::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
#if PRINTEVENTS == 1
		std::cout << "mouse_position_callback:\n\txpos: " << xpos << ", ypos: " << ypos << std::endl;
#endif
		for (size_t i = 0; i < observers[POSITION].size(); i++) {
			observers[POSITION].at(i)->notifyMousePositionEvent(xpos, ypos);
		}
	}

	void MouseListener::mouse_enter_callback(GLFWwindow* window, int entered)
	{
#if PRINTEVENTS == 1
		std::cout << "mouse_enter_callback:\n\tentered: " << entered << std::endl;
#endif
		for (size_t i = 0; i < observers[ENTER].size(); i++) {
			observers[ENTER].at(i)->notifyMouseEnterEvent(entered);
		}
	}

	void MouseListener::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
#if PRINTEVENTS == 1
		std::cout << "mouse_button_callback:\n\tbutton: " << button << ", action: " << action << ", mods: " << mods << std::endl;
#endif
		for (size_t i = 0; i < observers[BUTTON].size(); i++) {
			observers[BUTTON].at(i)->notifyMouseButtonEvent(button, action, mods);
		}
	}

	void MouseListener::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
#if PRINTEVENTS == 1
		std::cout << "mouse_scroll_callback:\n\txoffset: " << xoffset << ", yoffset: " << yoffset << std::endl;
#endif
		for (size_t i = 0; i < observers[SCROLL].size(); i++) {
			observers[SCROLL].at(i)->notifyMouseScrollEvent(xoffset, yoffset);
		}
	}
}