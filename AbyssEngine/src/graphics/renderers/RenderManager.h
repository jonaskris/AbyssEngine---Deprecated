#pragma once
#include <vector>
#include "Renderer.h"

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
		std::vector<Renderer*> renderers;
	public:
		static RenderManager* getInstance();
		~RenderManager();
		void render(std::vector<Scene*>& scenes);
		bool windowClosed();
	};
}