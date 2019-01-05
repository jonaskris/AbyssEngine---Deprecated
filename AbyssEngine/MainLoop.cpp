#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <map>
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
#include "math/sets/Set.h"
#include "math/sets/Map.h"
#include "config/ConfigReader.h"
#include "config/ConfigToken.h"


int main() 
{
	Renderer* renderer = Renderer::getInstance();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	WorldScene* scene = new WorldScene();
	std::vector<Scene*> scenes;
	scenes.push_back((Scene*)scene);


	// Renderloop

	double target_fps = 0; // 0 is no cap
	double target_time = (target_fps != 0) ? 1000000000 / target_fps : 0;

	double deltaTime = 0.0;
	double fps = 0.0;

	while (!renderer->windowClosed()) 
	{
		auto start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < scenes.size(); i++)
			{
				KeyboardListener::update();
				scenes.at(i)->update(deltaTime);
			}
			renderer->render(scenes);

		auto finish = std::chrono::high_resolution_clock::now();
		double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count());

		deltaTime = timeTaken / (1000000000 / 1.0f);
		fps = 1000000000 / timeTaken;
		std::cout << fps << std::endl;
	}
	// Renderloop
}