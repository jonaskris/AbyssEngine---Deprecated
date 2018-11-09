#pragma once
#include "../Window.h"
#include <vector>
#include "../shaders/Shader.h"
#include "../../scenes/Scene.h"
#include "../../entities/components/gComponent/GSSComponent.h"
#include <vector>

class Renderer
{
private:
	int width, height;
	Window* window;

public:
	Renderer();
	~Renderer();
	void render(std::vector<GSSComponent*>* gssComponents);
	bool windowClosed();
	void clear(); // Temporary
	void update(); // Temporary
};
	
