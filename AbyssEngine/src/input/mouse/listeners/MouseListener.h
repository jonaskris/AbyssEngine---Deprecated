#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../InputEnums.h"
#include "../../../math/linalg.h"

namespace abyssengine {
	class MouseObserver;

	namespace MouseListener {

		struct ButtonState
		{
			math::vec2f lastPressedPosition;
			bool pressed = false;
			bool pressedThisUpdate = false;
			bool releasedThisUpdate = false;
		};

		static math::vec2f lastPosition;

		static std::map<Mouse::Button, ButtonState> buttonStates;

		enum MouseListenerType { POSITION, ENTER, BUTTON, SCROLL, DRAG };
		static std::vector<MouseObserver*> observers[5];

		void addObserver(MouseObserver& observer, MouseListenerType type);
		void removeObserver(MouseObserver& observer, MouseListenerType type);

		void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
		void mouse_enter_callback(GLFWwindow* window, int entered);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		void update();
	}
}