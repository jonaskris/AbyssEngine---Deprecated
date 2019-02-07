#include <vector>
#include "Renderer.h"
#include <GL/glew.h>
#include "../Window.h"
#include "../shaders/Program.h"
#include "SpriteRenderer.h"
#include "LineRenderer.h"
#include "PointRenderer.h"
#include "../../math/mat4.h"
#include "../../entities/Entity.h"
#include "../../scenes/Scene.h"
#include "../../entities/components/PComponent.h"
#include "../../entities/components/gComponent/GSSComponent.h"
#include "../../entities/components/gComponent/GLComponent.h"
#include "../../entities/components/gComponent/GPComponent.h"
#include "../../entities/components/CComponent.h"
//#include "../Font.h"

#define DRAW_COLLISION_BOUNDS true 
#define DRAW_FRUSTUM_CENTER true

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
		width = (int)(1920 / (1.5f));
		height = (int)(1080 / (1.5f));

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

		struct SceneCollisionBounds
		{
			std::vector<GLComponent*> lines;
			Camera* camera;
		};
		std::vector<SceneCollisionBounds> collisionBounds;

		struct SceneGraphicsCenters
		{
			std::vector<GPComponent*> points;
			Camera* camera;
		};
		std::vector<SceneGraphicsCenters> graphicsCenters;

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
			SceneGraphicsCenters sceneGraphicsCenters;
			sceneGraphicsCenters.camera = scenes.at(i)->getCamera();

			camera->beginFrustumCulling();


			for (size_t j = 0; j < sceneEntities.size(); j++)
			{
				PComponent* pComponent = sceneEntities.at(j)->getPComponent();
				std::vector<GComponent*> gComponents = sceneEntities.at(j)->getGComponents();
				for (size_t h = 0; h < gComponents.size(); h++)
				{
					if (camera->inFrustum(gComponents.at(h)))
					{
						components[gComponents.at(h)->getType()].push_back(gComponents.at(h));
						if (DRAW_FRUSTUM_CENTER)
						{
							sceneGraphicsCenters.points.push_back(new GPComponent(math::vec3(0.0f, 0.0f, 0.0f)));
							sceneGraphicsCenters.points[sceneGraphicsCenters.points.size() - 1]->pComponent = pComponent;
						}
					}
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

			if (DRAW_FRUSTUM_CENTER)
			{
				graphicsCenters.push_back(sceneGraphicsCenters);
			}

			std::vector<GSSComponent*> gssComponents;
			for (GComponent* component : components[GComponent::gComponentType::GSSComponentType]) { gssComponents.push_back((GSSComponent*)component); }

			std::vector<GLComponent*> glComponents;
			for (GComponent* component : components[GComponent::gComponentType::GLComponentType]) { glComponents.push_back((GLComponent*)component); }

			std::vector<GPComponent*> gpComponents;
			for (GComponent* component : components[GComponent::gComponentType::GPComponentType]) { gpComponents.push_back((GPComponent*)component); }

			drewCount += gssComponents.size() + glComponents.size();
			SpriteRenderer::getInstance()->render(gssComponents, scenes.at(i)->getCamera());
			LineRenderer::getInstance()->render(glComponents, scenes.at(i)->getCamera());
			PointRenderer::getInstance()->render(gpComponents, scenes.at(i)->getCamera());
		}

		if (DRAW_COLLISION_BOUNDS)
		{
			glClear(GL_DEPTH_BUFFER_BIT);
			for (size_t i = 0; i < collisionBounds.size(); i++)
			{
				drewCount += collisionBounds.at(i).lines.size();
				LineRenderer::getInstance()->render(collisionBounds.at(i).lines, collisionBounds.at(i).camera);
				for (size_t j = 0; j < collisionBounds.at(i).lines.size(); j++) {
					delete collisionBounds.at(i).lines[j];
				}
			}
		}

		if (DRAW_FRUSTUM_CENTER)
		{
			glClear(GL_DEPTH_BUFFER_BIT);
			for (size_t i = 0; i < graphicsCenters.size(); i++)
			{
				drewCount += graphicsCenters.at(i).points.size();
				PointRenderer::getInstance()->render(graphicsCenters.at(i).points, graphicsCenters.at(i).camera);
				for (size_t j = 0; j < graphicsCenters.at(i).points.size(); j++) {
					delete graphicsCenters.at(i).points[j];
				}
			}
		}

		std::cout << "Drew " << drewCount << " GComponents." << std::endl;

		window->update();
	}
}