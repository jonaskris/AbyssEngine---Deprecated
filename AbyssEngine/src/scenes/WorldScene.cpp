#include "WorldScene.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/geometry/Shape.h"
#include "../resources/Texture.h"
#include "../resources/TextureAtlas.h"
#include "../entitysystem/DefaultComponents.h"
#include "../entitysystem/DefaultGComponents.h"
#include "../entitysystem/DefaultSystems.h"
#include "../resources/ResourceManager.h"
#include "../Defines.h"

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
		// Register systems, systems are executed in the order they are registered.
		entityManager.registerSystem(new Test_Movement());
		entityManager.registerSystem(new Camera_Movement());

		// Axis
		entityManager.newEntity(Line_Component{ math::vec3{ 0.0f, 0.0f, 0.0f }, math::vec3{ 1.0f, 0.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		entityManager.newEntity(Line_Component{ math::vec3{ 0.0f, 0.0f, 0.0f }, math::vec3{ 0.0f, 1.0f, 0.0f }, math::vec4{0.0f, 1.0f, 0.0f, 1.0f} });
		entityManager.newEntity(Line_Component{ math::vec3{ 0.0f, 0.0f, 0.0f }, math::vec3{ 0.0f, 0.0f, 1.0f }, math::vec4{0.0f, 0.0f, 1.0f, 1.0f} });

		// Generate the scene
		entityManager.newEntity(Line_Component{ math::vec3{ -3.0f, -3.0f, 0.0f }, math::vec3{ 3.0f, -3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		entityManager.newEntity(Line_Component{ math::vec3{ 3.0f, -3.0f, 0.0f }, math::vec3{ 3.0f, 3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		entityManager.newEntity(Line_Component{ math::vec3{ 3.0f, 3.0f, 0.0f }, math::vec3{ -3.0f, 3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		entityManager.newEntity(Line_Component{ math::vec3{ -3.0f, 3.0f, 0.0f }, math::vec3{ -3.0f, -3.0f, 0.0f }, math::vec4{1.0f, 0.0f, 0.0f, 1.0f} });
		
		float speed = 3.5f;

		size_t countPoints = 10000;
		for (size_t i = 0; i < countPoints; i++)
		{
			float angle = math::toRadians( ((float)rand() / (float)RAND_MAX) * 360.0f);

			entityManager.newEntity(Point_Component{ math::vec3{ 0.0f, 0.0f, 0.0f}, math::vec4{ 1.0f, 1.0f, 1.0f, 1.0f } }, Velocity_Component{ math::vec3{ sin(angle) * speed, cos(angle) * speed, 0.0f } });
		}

		entityManager.newEntity(Sprite_Component{ "testSheet1", 7, 1.0f});
		entityManager.newEntity(Camera_Component(FOV, ASPECT_RATIO, NEAR, FAR));

	}

	void WorldScene::update(const double &dt)
	{
		entityManager.update(dt);
	}
}