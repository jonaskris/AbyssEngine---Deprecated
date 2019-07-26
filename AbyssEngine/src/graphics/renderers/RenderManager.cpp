#include <vector>
#include "RenderManager.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "../../entitysystem/entitymanager/EntityManager.h"
#include "SpriteRenderer.h"
#include "LineRenderer.h"
#include "PointRenderer.h"
#include "../../math/linalg.h"
#include "../../scenes/Scene.h"
#include "../../Defines.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/defaultcomponents/Graphics.h"
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

		renderers.push_back(new SpriteRenderer());
		renderers.push_back(new LineRenderer());
		renderers.push_back(new PointRenderer());


		
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
			entitysystem::EntityManager* entityManager = scenes.at(i)->getEntityManager();
			auto cameras = entityManager->getUnitVector<Camera_Component>();
			Camera_Component& camera = cameras->at(0);

			math::mat4f perspectiveViewMatrix = camera.perspective * camera.viewMatrix;

			for (size_t i = 0; i < renderers.size(); i++)
			{
				renderers.at(i)->begin(perspectiveViewMatrix);
				renderers.at(i)->submitUnits(entityManager);
				renderers.at(i)->end();
			}
		}
		window->update();
	}
}