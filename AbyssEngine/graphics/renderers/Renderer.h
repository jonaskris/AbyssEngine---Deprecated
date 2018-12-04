#pragma once
#include <vector>
#include "../Camera.h"

class Window;
class GSSComponent;
class Entity;
class Scene;

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
	void render(std::vector<Scene*>& scenes);
	bool windowClosed();
	void clear(); // Temporary
	void update(); // Temporary
};