#pragma once
#include <iostream>
#include <vector>
#include "../observers/MouseObserver.h"
#include "../observers/MousePositionObserver.h"
#include "../observers/MouseEnterObserver.h"
#include "../observers/MouseButtonObserver.h"
#include "../observers/MouseScrollObserver.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace MouseListener {
	enum MOUSELISTENER{POSITION, ENTER, BUTTON, SCROLL};
	static std::vector<MouseObserver*> observers[4];
	void addObserver(MouseObserver& observer, MOUSELISTENER MOUSELISTENER);
	void removeObserver(MouseObserver& observer, MOUSELISTENER MOUSELISTENER);
	bool findObserver(MouseObserver& observer, MOUSELISTENER MOUSELISTENER);
	int getObserversSize(MOUSELISTENER MOUSELISTENER);
	int getObserversSize();
	void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_enter_callback(GLFWwindow* window, int entered);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}
