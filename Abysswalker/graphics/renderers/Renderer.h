#pragma once
#include <vector>

class Window;
class GSSComponent;
class Entity;

class Renderer
{
private:
	Renderer();
	static Renderer* instance;
	int width, height;
	Window* window;
public:
	static Renderer* getInstance();
	~Renderer();
	void render(std::vector<Entity*>& entities);
	bool windowClosed();
	void clear(); // Temporary
	void update(); // Temporary
};
	
