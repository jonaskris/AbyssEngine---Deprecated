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

#include "../TextureAtlas.h"
#include "../Camera.h"
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
		TextureAtlas::loadAtlases();

		
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

		// For every scene
			// Get camera
				// If it doesent have projection matrix, create one for it
			// Get graphics components from scene, and give them to renderers that can render their type
			// Update window
			
		for (size_t i = 0; i < scenes.size(); i++)
		{
			Camera* camera = scenes.at(i)->getCamera();
		
			if (camera->getProjectionMatrix() == NULL)
				camera->setProjectionMatrix(FOV, ASPECT_RATIO, NEAR, FAR);

			auto pointComponents = scenes.at(i)->getEntityManager().getComponentVectorByType<Point_Component>();
			if(pointComponents)
				PointRenderer::getInstance()->render(pointComponents, camera);

			auto lineComponents = scenes.at(i)->getEntityManager().getComponentVectorByType<Line_Component>();
			if(lineComponents)
				LineRenderer::getInstance()->render(lineComponents, camera);

			auto spriteSheetComponents = scenes.at(i)->getEntityManager().getComponentVectorByType<SpriteSheet_Component>();
			if (spriteSheetComponents)
				SpriteRenderer::getInstance()->render(spriteSheetComponents, camera);
		}



		

		window->update();
	}
}