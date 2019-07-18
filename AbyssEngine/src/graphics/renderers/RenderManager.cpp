#include <vector>
#include "RenderManager.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "LineRenderer.h"
#include "PointRenderer.h"
#include "../../math/mat4.h"
#include "../../scenes/Scene.h"
#include "../../Defines.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/DefaultComponents.h"
#include "../../resources/ResourceManager.h"

//#define DRAW_COLLISION_BOUNDS true 
//#define DRAW_FRUSTUM_CENTER true

namespace abyssengine {
	RenderManager* RenderManager::instance = NULL;
	RenderManager* RenderManager::getInstance()
	{
		if (!instance)
		{
			std::cout << "Initialized RenderManager singleton!" << std::endl;
			instance = new RenderManager();
			return instance;
		}
		return instance;
	}

	RenderManager::RenderManager()
	{
		width = (int)(SCREEN_WIDTH / (1.5f));
		height = (int)(SCREEN_HEIGHT / (1.5f));

		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
		}
		window = new Window(WINDOW_NAME, width, height);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Program::loadPrograms();
		ResourceManager::getInstance();

		
		//Font::initFonts();
	}

	RenderManager::~RenderManager()
	{
		delete window;
	}

	bool RenderManager::windowClosed() {
		return window->closed();
	}

	void RenderManager::render(std::vector<Scene*>& scenes)
	{
		window->clear();
			
		for (size_t i = 0; i < scenes.size(); i++)
		{
			EntityManager* entityManager = scenes.at(i)->getEntityManager();
			auto cameras = entityManager->getUnitVector<Camera_Component>();
			Camera_Component& camera = cameras->at(0);

			math::mat4 perspectiveViewMatrix = camera.perspective * camera.viewMatrix;

			auto pointComponents = entityManager->getUnitVector<Point_Component>();
			if(pointComponents)
				PointRenderer::getInstance()->render(pointComponents, perspectiveViewMatrix);

			auto lineComponents = entityManager->getUnitVector<Line_Component>();
			if(lineComponents)
				LineRenderer::getInstance()->render(lineComponents, perspectiveViewMatrix);

			auto spriteComponents = entityManager->getUnitVector<Sprite_Component>();
			if (spriteComponents)
				SpriteRenderer::getInstance()->render(spriteComponents, perspectiveViewMatrix);
		}



		

		window->update();
	}
}