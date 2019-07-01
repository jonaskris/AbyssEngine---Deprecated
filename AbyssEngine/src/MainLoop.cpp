#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <map>
#include <thread>
#include <algorithm>
#include "scenes/WorldScene.h"
#include "input/listeners/KeyboardListener.h"
#include "graphics/renderers/Renderer.h"

int main()
{
	using namespace abyssengine;
	Renderer* renderer = Renderer::getInstance();
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

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

	while (!renderer->windowClosed())
	{
		oldTime = newTime;
		newTime = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < scenes.size(); i++)
			{
				//KeyboardListener::update();
				scenes.at(i)->update(deltaTime);
			}
			renderer->render(scenes);


		long long timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - oldTime).count();

		deltaTime = (double)timeTaken / (double)1000;

		timer += deltaTime;
		frameCount++;

		if (timer > 1.0f)
		{
			std::cout << frameCount << std::endl;
			timer = 0.0f;
			frameCount = 0;
		}
	}
}