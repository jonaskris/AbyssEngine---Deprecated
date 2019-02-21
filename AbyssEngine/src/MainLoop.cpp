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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	WorldScene* scene = new WorldScene();
	std::vector<Scene*> scenes;
	scenes.push_back((Scene*)scene);


	double target_fps = 0; // 0 is no cap
	double target_time = (target_fps != 0) ? 1000000000 / target_fps : 0;

	double deltaTime = 0.0;
	double fps = 0.0;

	while (!renderer->windowClosed())
	{
		auto start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < scenes.size(); i++)
			{
				//KeyboardListener::update();
				scenes.at(i)->update(deltaTime);
			}
			renderer->render(scenes);

		auto finish = std::chrono::high_resolution_clock::now();
		double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count());

		deltaTime = timeTaken / (1000000000 / 1.0f);
		fps = 1000000000 / timeTaken;
		//std::cout << fps << std::endl;
	}

	/*struct obj 
	{
		int number;

		bool operator < (const obj& other) const
		{
			return (number < other.number);
		}
	};


	std::vector<obj> ints;
	ints.push_back(obj{4});
	ints.push_back(obj{1});
	ints.push_back(obj{7});
	ints.push_back(obj{2});

	for (size_t i = 0; i < ints.size(); i++) {
		std::cout << ints.at(i).number << std::endl;
	}
	std::cout << std::endl;
	
	std::sort(ints.begin(), ints.end());

	for (size_t i = 0; i < ints.size(); i++) {
		std::cout << ints.at(i).number << std::endl;
	}
	std::cout << std::endl;


	system("PAUSE");*/
}