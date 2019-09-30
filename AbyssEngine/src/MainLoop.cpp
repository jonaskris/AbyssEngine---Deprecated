#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <map>
#include <thread>
#include <algorithm>
#include <filesystem>
#include "scenes/WorldScene.h"
#include "graphics/rendermanager/RenderManager.h"
#include "math/semantics/Time.h"
#include "resources/resourcemanager/ResourceManager.h"
#include "resources/Path.h"
#include "resources/File/File.h"
#include "input/keyboard/listeners/KeyboardListener.h"
#include "input/mouse/listeners/MouseListener.h"

int main()
{

	using namespace abyssengine;
	using namespace resources;

	graphics::RenderManager* renderManager = new graphics::RenderManager();

	ResourceManager* resourceManager = ResourceManager::initInstance(RESOURCE_DIRECTORY);
	
	WorldScene* scene = new WorldScene();
	std::vector<Scene*> scenes;
	scenes.push_back((Scene*)scene);


	//double target_fps = 0; // 0 is no cap
	//double target_time = (target_fps != 0) ? 1000000000 / target_fps : 0;
	
	double deltaTime = 0.0;
	double fps = 0.0;
	double timer = 0;
	double frameCount = 0;
	
	auto oldTime = std::chrono::high_resolution_clock::now();
	auto newTime = std::chrono::high_resolution_clock::now();
	
	while (!renderManager->getWindowClosed())
	{
		oldTime = newTime;
		newTime = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < scenes.size(); i++)
				scenes.at(i)->update(math::Time{ (float)deltaTime });

		renderManager->render(scenes);

		input::KeyboardListener::update();
		input::MouseListener::update();
	
		long long timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - oldTime).count();
	
		deltaTime = (double)timeTaken / (double)1000;
	
		timer += deltaTime;
		frameCount++;
	
		if (timer > 1.0f)
		{
			std::cout << "FPS: " << frameCount << std::endl;
			std::cout << "Deltatime: " << deltaTime << std::endl;
			timer = 0.0f;
			frameCount = 0;
		}
	}
}