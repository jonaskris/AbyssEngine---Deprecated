#pragma once
#include <vector>

namespace abyssengine {
	class Window;
	class Scene;

	/*
		Manages Renderers and the Window.
	*/
	class RenderManager
	{
	private:
		RenderManager();
		static RenderManager* instance;
		int width, height;
		Window* window = NULL;
	public:
		static RenderManager* getInstance();
		~RenderManager();
		void render(std::vector<Scene*>& scenes);
		bool windowClosed();
	};
}