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
#include "math/sets/Set.h"
#include "math/sets/Map.h"


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

	/*std::vector<int> a;
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	Set<int> sa(a);

	std::vector<int> b;
	b.push_back(7);
	b.push_back(8);
	b.push_back(9);
	Set<int> sb(b);

	math::Map<int, int> map;
	map.addConnection(0, 4);
	map.addConnection(1, 8);
	map.addConnection(2, 2);

	Set<int> result = map.map(sa);
	
	result.printout();

	system("PAUSE");*/
}