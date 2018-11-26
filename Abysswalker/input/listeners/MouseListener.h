#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MouseObserver;

namespace MouseListener {
	enum MouseListenerType{POSITION, ENTER, BUTTON, SCROLL};
	static std::vector<MouseObserver*> observers[4];
	void addObserver(MouseObserver& observer, MouseListenerType type);
	void removeObserver(MouseObserver& observer, MouseListenerType type);
	bool findObserver(MouseObserver& observer, MouseListenerType type);
	int getObserversSize(MouseListenerType type);
	int getObserversSize();
	void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_enter_callback(GLFWwindow* window, int entered);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}
