#include "WorldScene.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/geometry/Shape.h"
#include "../graphics/TextureAtlas.h"
#include "../entitysystem/Components.h"
#include "../entitysystem/GComponents.h"
#include "../entitysystem/Systems.h"

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
		// Register systems
		entityManager.registerSystem<Test_Movement_System>();



		// Generate the scene
		//entityManager.newEntity(Line_Component{ math::vec3{ -3.0f, -3.0f, 0.0f }, math::vec3{ 3.0f, -3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		//entityManager.newEntity(Line_Component{ math::vec3{ 3.0f, -3.0f, 0.0f }, math::vec3{ 3.0f, 3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		//entityManager.newEntity(Line_Component{ math::vec3{ 3.0f, 3.0f, 0.0f }, math::vec3{ -3.0f, 3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		//entityManager.newEntity(Line_Component{ math::vec3{ -3.0f, 3.0f, 0.0f }, math::vec3{ -3.0f, -3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		//
		//size_t countPoints = 10000;
		//for (size_t i = 0; i < countPoints; i++)
		//{
		//	float angle = math::toRadians((rand() / (float)RAND_MAX) *  360.0f);
		//	entityManager.newEntity(Point_Component{ math::vec3{ 0.0f, 0.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f } }, Velocity_Component{ math::vec3{ sinf(angle), cosf(angle), 0.0f } / 50.0f });
		//}

		entityManager.newEntity(SpriteSheet_Component{ 0, 1.0f, TextureAtlas::getAtlas(0)->getTextureCoordinates(7)});
		camera = new Camera();
	}

	void WorldScene::update(const double &dt)
	{
		entityManager.update(dt);
	}
}