#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "../input/keyboard/listeners/KeyboardListener.h"
#include "../input/mouse/listeners/MouseListener.h"

namespace abyssengine {
	namespace graphics {
		void windowResize(GLFWwindow* window, int width, int height);
		Window::Window(const char* title, int width, int height)
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

			glfwSetKeyCallback(window, input::KeyboardListener::key_callback);
			glfwSetCursorPosCallback(window, input::MouseListener::mouse_position_callback);
			glfwSetCursorEnterCallback(window, input::MouseListener::mouse_enter_callback);
			glfwSetMouseButtonCallback(window, input::MouseListener::mouse_button_callback);
			glfwSetScrollCallback(window, input::MouseListener::mouse_scroll_callback);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

		void windowResize(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}
}