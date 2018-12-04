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

	for (size_t i = 0; i < scenes.size(); i++) 
	{
		std::vector<Entity*> sceneEntities = scenes.at(i)->getEntities();

		std::vector<GComponent*> components[GComponent::getComponentTypeCount()];



		SceneCollisionBounds sceneCollisionBounds;
		sceneCollisionBounds.camera = scenes.at(i)->getCamera();

		for (size_t j = 0; j < sceneEntities.size(); j++)
		{
			std::vector<GComponent*> gComponents = sceneEntities.at(j)->getGComponents();
			for (size_t h = 0; h < gComponents.size(); h++)
			{
				components[gComponents.at(h)->getType()].push_back(gComponents.at(h));
			}

			if (DRAW_COLLISION_BOUNDS)
			{
				std::vector<CComponent*> cComponents = sceneEntities.at(j)->getCComponents();

				for (size_t k = 0; k < cComponents.size(); k++)
				{
					std::vector<GLComponent*> cComponentsGLComponents = cComponents.at(k)->getGLComponents();
					sceneCollisionBounds.lines.insert(sceneCollisionBounds.lines.end(), cComponentsGLComponents.begin(), cComponentsGLComponents.end());
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

		Camera* camera = scenes.at(i)->getCamera();
		GComponent* player = components[GComponent::gComponentType::GSSComponentType].at(100);
		SpriteRenderer::getInstance()->render(gssComponents, mat4::perspective(90.0f, width/(float)height, 1.0f, 4.0f), camera->getLookatMat());
		LineRenderer::getInstance()->render(glComponents, mat4::perspective(90.0f, width / (float)height, 1.0f, 4.0f), camera->getLookatMat());
	}

	if (DRAW_COLLISION_BOUNDS)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		for (size_t i = 0; i < collisionBounds.size(); i++)
		{
			LineRenderer::getInstance()->render(collisionBounds.at(i).lines, mat4::perspective(90.0f, width / (float)height, 1.0f, 4.0f), collisionBounds.at(i).camera->getLookatMat());
		}
	}

	window->update();
}

void Renderer::clear() { // Temporary
	window->clear();
}

void Renderer::update() { // Temporary
	window->update();
}