#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <thread>
#include "graphics/renderers/Renderer.h"
#include "graphics/TextureAtlas.h"
#include "entities/Entity.h"
#include "entities/Entity_Test.h"
#include "entities/Entity_Ground.h"
#include "entities/EntityFactory.h"
#include "entities/components/gComponent/GSSComponent.h"
#include "input/listeners/KeyboardListener.h"
#include "scenes/WorldScene.h"


int main() 
{
	Renderer* renderer = Renderer::getInstance();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	WorldScene* scene = new WorldScene();
	std::vector<Scene*> scenes;
	scenes.push_back((Scene*)scene);

	while (!renderer->windowClosed()) 
	{
		for (size_t i = 0; i < scenes.size(); i++)
		{
			scenes.at(i)->update();
		}
		renderer->render(scenes);
		// std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}