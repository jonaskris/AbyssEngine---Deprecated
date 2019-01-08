#include <vector>
#include "Renderer.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "LineRenderer.h"
#include "../../math/mat4.h"
#include "../../entities/Entity.h"
#include "../../scenes/Scene.h"
#include "../../entities/components/PComponent.h"
#include "../../entities/components/gComponent/GSSComponent.h"
#include "../../entities/components/gComponent/GLComponent.h"
#include "../../entities/components/CComponent.h"

#define DRAW_COLLISION_BOUNDS true 
#define DRAW_VIEW_FRUSTUM false 

Renderer* Renderer::instance;

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
	width = (int)(1920/(1.5f));
	height = (int)(1080/(1.5f));

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
	}
	window = new Window("Abysswalker", width, height);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Program::loadPrograms();
	TextureAtlas::loadAtlases();
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

	struct SceneCollisionBounds
	{
		std::vector<GLComponent*> lines;
		Camera* camera;
	};
	std::vector<SceneCollisionBounds> collisionBounds;

	int drewCount = 0;

	for (size_t i = 0; i < scenes.size(); i++) 
	{
		Camera* camera = scenes.at(i)->getCamera();
		if (camera == NULL)
		{
			std::cout << "Tried rendering scene, but it doesent have a camera!" << std::endl;
			continue;
		}

		if (camera->getProjectionMatrix() == NULL)
			camera->setProjectionMatrix(90.0f, width / (float)height, 1.0f, 4.0f);


		std::vector<Entity*> sceneEntities = scenes.at(i)->getEntities();

		std::vector<GComponent*> components[GComponent::getComponentTypeCount()];

		SceneCollisionBounds sceneCollisionBounds;
		sceneCollisionBounds.camera = scenes.at(i)->getCamera();
		camera->beginFrustumCulling();
		

		for (size_t j = 0; j < sceneEntities.size(); j++)
		{
			std::vector<GComponent*> gComponents = sceneEntities.at(j)->getGComponents();
			for (size_t h = 0; h < gComponents.size(); h++)
			{
				if(camera->inFrustum(gComponents.at(h)))
				components[gComponents.at(h)->getType()].push_back(gComponents.at(h));
			}

			if (DRAW_COLLISION_BOUNDS)
			{
				std::vector<CComponent*> cComponents = sceneEntities.at(j)->getCComponents();

				for (size_t k = 0; k < cComponents.size(); k++)
				{
					std::vector<GLComponent*> cComponentsGLComponents = cComponents.at(k)->getGLComponents();

					for (size_t f = 0; f < cComponentsGLComponents.size(); f++)
					{
						if (camera->inFrustum(cComponentsGLComponents.at(f)))
							sceneCollisionBounds.lines.push_back(cComponentsGLComponents.at(f));
					}
				}
			}
		}

		if (DRAW_COLLISION_BOUNDS)
		{
			collisionBounds.push_back(sceneCollisionBounds);
		}

		std::vector<GSSComponent*> gssComponents;
		for (GComponent* component : components[GComponent::gComponentType::GSSComponentType]) { gssComponents.push_back((GSSComponent*)component); }

		std::vector<GLComponent*> glComponents;
		for (GComponent* component : components[GComponent::gComponentType::GLComponentType]) { glComponents.push_back((GLComponent*)component); }

		if(DRAW_VIEW_FRUSTUM)
		{
			glComponents.push_back(new GLComponent(camera->farBottomLeft, camera->farTopLeft));
			glComponents.push_back(new GLComponent(camera->farTopLeft, camera->farTopRight));
			glComponents.push_back(new GLComponent(camera->farTopRight, camera->farBottomRight));
			glComponents.push_back(new GLComponent(camera->farBottomRight, camera->farBottomLeft));
		}

		drewCount += gssComponents.size() + glComponents.size();
		SpriteRenderer::getInstance()->render(gssComponents, scenes.at(i)->getCamera());
		LineRenderer::getInstance()->render(glComponents, scenes.at(i)->getCamera());
	}

	if (DRAW_COLLISION_BOUNDS)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		for (size_t i = 0; i < collisionBounds.size(); i++)
		{
			drewCount += collisionBounds.at(i).lines.size();
			LineRenderer::getInstance()->render(collisionBounds.at(i).lines, collisionBounds.at(i).camera);
		}
	}

	std::cout << "Drew " << drewCount << " GComponents." << std::endl;

	window->update();
}