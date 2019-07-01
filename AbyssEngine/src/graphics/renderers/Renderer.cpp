#include <vector>
#include "Renderer.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "LineRenderer.h"
#include "PointRenderer.h"
#include "../../math/mat4.h"
//#include "../../entities/Entity.h"
#include "../../scenes/Scene.h"
#include "../../Defines.h"
//#include "../../entities/components/Position_Component.h"
//#include "../../entities/components/Graphics_Component.h"
//#include "../../entities/components/Collision_Component.h"
#include "../../resources/Texture.h"
#include "../../entitysystem/DefaultComponents.h"
#include "../../resources/ResourceManager.h"
//#include "../Font.h"

//#define DRAW_COLLISION_BOUNDS true 
//#define DRAW_FRUSTUM_CENTER true

namespace abyssengine {
	Renderer* Renderer::instance = NULL;
	Renderer* Renderer::getInstance()
	{
		if (!instance)
		{
			std::cout << "Initialized Renderer singleton!" << std::endl;
			instance = new Renderer();
			return instance;
		}
		return instance;
	}

	Renderer::Renderer()
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

	Renderer::~Renderer()
	{
		delete window;
	}

	bool Renderer::windowClosed() {
		return window->closed();
	}

	void Renderer::render(std::vector<Scene*>& scenes)
	{
		window->clear();
			
		for (size_t i = 0; i < scenes.size(); i++)
		{
			EntityManager* entityManager = scenes.at(i)->getEntityManager();
			auto cameras = entityManager->getComponentVectorByType<Camera_Component>();
			Camera_Component& camera = cameras->at(0);

			math::mat4 perspectiveViewMatrix = camera.perspective * camera.viewMatrix;

			auto pointComponents = entityManager->getComponentVectorByType<Point_Component>();
			if(pointComponents)
				PointRenderer::getInstance()->render(pointComponents, perspectiveViewMatrix);

			auto lineComponents = entityManager->getComponentVectorByType<Line_Component>();
			if(lineComponents)
				LineRenderer::getInstance()->render(lineComponents, perspectiveViewMatrix);

			auto spriteComponents = entityManager->getComponentVectorByType<Sprite_Component>();
			if (spriteComponents)
				SpriteRenderer::getInstance()->render(spriteComponents, perspectiveViewMatrix);
		}



		

		window->update();
	}
}