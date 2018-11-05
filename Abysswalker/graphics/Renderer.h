#pragma once
#include "Window.h"

class Renderer
{
private:
	int width, height;
	Window* window;
public:
	Renderer();
	~Renderer();
	void render();
	bool windowClosed();
		void clear(); // Temp
		void update(); // Temp
};

