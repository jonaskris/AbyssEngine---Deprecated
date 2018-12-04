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
	size_t count = 100;
	size_t root = (size_t)sqrt(count); 
	vec3 startPos(0.0f, 0.0f, 0.0f);
	vec2 scale(10.0f, 10.0f);

	for (size_t y = 0; y < root; y++)
	{
		for (size_t x = 0; x < root; x++)
		{
			std::vector<Component*> components;
			components.push_back(new PComponent(vec3(startPos.x + x * scale.x, startPos.y + y * scale.y, startPos.z)));
			components.push_back(new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 1, scale));
			components.push_back(new CComponent(Shape::shape::BOX, scale));
			entities.push_back(new Entity_Ground(components));
		}
	}

	std::vector<Component*> components;
	components.push_back(new PComponent(vec3(0.0f, 0.0f, 0.01f)));
	components.push_back(new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 2, scale / 2));

	Entity* player = new Entity_Player(components);
	entities.push_back(player);

	camera = new Camera(player->getPComponent(), vec3(0.0f, 0.0f, 20.0f));
}


void WorldScene::update()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities.at(i)->update();
	}
}