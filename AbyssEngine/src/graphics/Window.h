#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace abyssengine {
	namespace graphics {
		class Window
		{
		private:
			int width, height;
			const char* title = NULL;
			GLFWwindow* window = NULL;
		public:
			Window(const char* title, int width, int height);
			~Window();
			void clear() const;
			void update() const;
			bool closed() const;
		};
	}
}