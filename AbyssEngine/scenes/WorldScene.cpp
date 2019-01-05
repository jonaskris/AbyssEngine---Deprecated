#include "WorldScene.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../entities/components/PComponent.h"
#include "../entities/components/gComponent/GSSComponent.h"
#include "../entities/components/Component.h"
#include "../entities/components/CComponent.h"
#include "../math/geometry/Shape.h"
#include "../graphics/TextureAtlas.h"
#include "../entities/Entity_Ground.h"
#include "../entities/Entity_Player.h"

WorldScene::WorldScene()
{
	generateScene();
}

WorldScene::~WorldScene()
{

}

void WorldScene::generateScene()
{
	size_t count = 1024;
	size_t root = (size_t)sqrt(count); 
	vec3 startPos(0.0f, 0.0f, 0.0f);
	vec2 gScale(10.0f, 10.0f);
	vec3 cScale(10.0f, 10.0f, 1.0f);


	std::vector<Component*> components;
	components.push_back(new PComponent(vec3(0.0f, 0.0f, 0.01f)));
	components.push_back(new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 2, gScale / 2));
	components.push_back(new CComponent(Shape::shape::BOX, cScale / 2));

	Entity* player = new Entity_Player(components);
	entities.push_back(player);

	for (size_t y = 0; y < root; y++)
	{
		for (size_t x = 0; x < root; x++)
		{
			std::vector<Component*> components;
			components.push_back(new PComponent(vec3(startPos.x + x * gScale.x, startPos.y + y * gScale.y, startPos.z)));
			components.push_back(new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 1, gScale));
			components.push_back(new CComponent(Shape::shape::BOX, cScale));
			entities.push_back(new Entity_Ground(components));
		}
	}

	camera = new Camera(player->getPComponent(), vec3(0.0f, 0.0f, 20.0f));
}


void WorldScene::update(double deltaTime)
{
	/*std::vector<CComponent*> cComponents;
	
	for (size_t i = 0; i < entities.size(); i++) 
	{
		std::vector<CComponent*> individualCComponents = entities.at(i)->getCComponents();
		cComponents.insert(cComponents.end(), individualCComponents.begin(), individualCComponents.end());
	}


	for (size_t i = 0; i < entities.size(); i++)
	{
		for (size_t j = i; j < entities.size(); j++) 
		{
			
		}
	}*/

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities.at(i)->preUpdate();
	}

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities.at(i)->update(deltaTime);
	}
}