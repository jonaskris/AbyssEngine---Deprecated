#include <iostream>
#include <vector>
#include <math.h>
#include "graphics/renderers/Renderer.h"
#include "graphics/TextureAtlas.h"
#include "entities/Entity.h"
#include "entities/Entity_Test.h"
#include "entities/EntityFactory.h"
#include "entities/components/gComponent/GSSComponent.h"

int main() 
{
	float pi = 3.1415926535897f;

	Renderer* renderer = Renderer::getInstance();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	vec3 speed(0.02f, 0.02f, 0.0f);
	vec3 boundaries(1.0f, 1.0f, 1.0f);
	vec2 scale(0.1f, 0.1f);

	std::vector<Entity*> entities;

	for (size_t i = 0; i < 5000; i++)
	{
		float directionAngle = (rand() / (float)RAND_MAX) * 2 * pi;
		std::vector<Component*> components;
		components.push_back(new GSSComponent(TextureAtlas::Atlas::TESTSHEET, (unsigned short)i, scale));
		entities.push_back(new Entity_Test(components, speed, vec3(sin(directionAngle), cos(directionAngle), 0.0f), boundaries));
	}

	while (true) 
	{
		
		for (size_t i = 0; i < entities.size(); i++) 
		{
			entities.at(i)->update();
		}
		renderer->render(entities);
	}

}