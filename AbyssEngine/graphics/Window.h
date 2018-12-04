#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	int width, height;
	const char *title;
	GLFWwindow *window;
public:
	Window(const char *title, int width, int height);
	~Window();
	void clear() const;
	void update() const;
	bool closed() const;
};