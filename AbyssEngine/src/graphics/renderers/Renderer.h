#pragma once
#include <vector>

namespace abyssengine {
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
		Window* window = NULL;
	public:
		static Renderer* getInstance();
		~Renderer();
		void render(std::vector<Scene*>& scenes);
		bool windowClosed();
	};
}