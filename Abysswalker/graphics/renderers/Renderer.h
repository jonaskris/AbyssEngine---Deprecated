#pragma once
#include <vector>

class Window;
class GSSComponent;

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
	
