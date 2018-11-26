#include <iostream>
#include <vector>
#include <math.h>
#include "graphics/renderers/Renderer.h"
#include "graphics/TextureAtlas.h"
#include "entities/Entity.h"
#include "entities/EntityFactory.h"

int main() 
{
	float pi = 3.1415926535897f;

	Renderer renderer;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	vec3 speed(0.02f, 0.02f, 0.0f);
	std::vector<GSSComponent*> components;
	std::vector<vec3> directions;
	PComponent* nullPointer = 0;

	for (size_t i = 0; i < 5000; i++)
	{
		float randDir = (rand() / (float)RAND_MAX) * 2 * pi;
		directions.push_back(vec3(sin(randDir), cos(randDir), 0));
		components.push_back(new GSSComponent(*nullPointer, TextureAtlas::Atlas::TESTSHEET, (unsigned short)i));
		components.back()->scale = vec2(0.1f, 0.1f);

	}

	while (true) 
	{
		for (size_t i = 0; i < components.size(); i++) {
			if (components.at(i)->position.x > 1.0f || components.at(i)->position.x < -1.0f) {
				directions.at(i) *= vec3(-1.0f, 1.0f, 1.0f);
			}
			if (components.at(i)->position.y > 1.0f || components.at(i)->position.y < -1.0f) {
				directions.at(i) *= vec3(1.0f, -1.0f, 1.0f);
			}

			components.at(i)->position += speed * directions.at(i);
		}

		renderer.render(&components);
	}

}