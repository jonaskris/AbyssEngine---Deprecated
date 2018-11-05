#pragma once
#include <iostream>
#include <vector>
#include "../observers/KeyboardObserver.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace KeyboardListener {
	static std::vector<KeyboardObserver*> observers;
	void addObserver(KeyboardObserver& observer);
	void removeObserver(KeyboardObserver& observer);
	bool findObserver(KeyboardObserver& observer);
	int getObserversSize();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool getPressed(int GLFW_KEY);
}
