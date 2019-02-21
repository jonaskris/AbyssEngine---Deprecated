#include "WorldScene.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../entities/components/Position_Component.h"
#include "../entities/components/Graphics_Component.h"
#include "../entities/components/Component.h"
#include "../entities/components/Collision_Component.h"
#include "../math/geometry/Shape.h"
#include "../graphics/TextureAtlas.h"

namespace abyssengine {
	WorldScene::WorldScene()
	{
		generateScene();
	}

	WorldScene::~WorldScene()
	{

	}

	void WorldScene::generateScene()
	{
		//size_t count = 128;
		//size_t root = (size_t)sqrt(count);
		//math::vec3 startPos(0.0f, 0.0f, 0.0f);
		//math::vec2 gScale(10.0f, 10.0f);
		//math::vec3 cScale(10.0f, 10.0f, 1.0f);
		//
		//std::vector<Component*> playercomponents;
		//PComponent* playerpComponent = new PComponent(math::vec3(0.0f, 0.0f, 0.01f));
		//playercomponents.push_back(playerpComponent);
		//GSSComponent* playergssComponent = new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 2, gScale / 2);
		//playercomponents.push_back(playergssComponent);
		//CComponent* playercComponent = new CComponent(Shape::shape::BOX, cScale / 2);
		//playercomponents.push_back(playercComponent);
		//
		//Entity* player = new Entity_Player(playercomponents);
		//entities.push_back(player);
		//
		//for (size_t y = 0; y < root; y++)
		//{
		//	for (size_t x = 0; x < root; x++)
		//	{
		//		std::vector<Component*> components;
		//		PComponent* pComponent = new PComponent(math::vec3(startPos.x + x * gScale.x, startPos.y + y * gScale.y, startPos.z));
		//		components.push_back(pComponent);
		//		GSSComponent* gssComponent = new GSSComponent(TextureAtlas::Atlas::TESTSHEET, 1, gScale);
		//		components.push_back(gssComponent);
		//		CComponent* cComponent = new CComponent(Shape::shape::BOX, cScale);
		//		components.push_back(cComponent);
		//		Entity* entity = new Entity_Ground(components);
		//		entities.push_back(entity);
		//	}
		//}
		//camera = new Camera(player->getPComponent(), math::vec3(0.0f, 0.0f, 20.0f));

		for (size_t i = 0; i < 128; i++) 
		{
			entityManager.newTestEntity();
		}
		camera = new Camera();
	}

	void WorldScene::update(const double &dt)
	{
		entityManager.update(dt);
	}
}