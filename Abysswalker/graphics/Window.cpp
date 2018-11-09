#include "Window.h"
#include "../input/listeners/KeyboardListener.h"
#include "../input/listeners/MouseListener.h"
#include <iostream>

void windowResize(GLFWwindow * window, int width, int height);

Window::Window(const char *title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, windowResize);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Could not initialize GLEW!" << std::endl;
	}

	glfwSetKeyCallback(window, KeyboardListener::key_callback);
	glfwSetCursorPosCallback(window, MouseListener::mouse_position_callback);
	glfwSetCursorEnterCallback(window, MouseListener::mouse_enter_callback);
	glfwSetMouseButtonCallback(window, MouseListener::mouse_button_callback);
	glfwSetScrollCallback(window, MouseListener::mouse_scroll_callback);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::update() const 
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Window::clear()  const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::closed() const
{
	return glfwWindowShouldClose(window) == 1;
}

void windowResize(GLFWwindow *window, int width, int height) 
{
	glViewport(0, 0, width, height);
}