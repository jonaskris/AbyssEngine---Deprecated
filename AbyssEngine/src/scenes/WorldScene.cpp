#include "WorldScene.h"
#include "../math/linalg.h"
#include "../math/geometry/Shape.h"
#include "../resources/Texture.h"
#include "../resources/TextureAtlas.h"
#include "../entitysystem/defaultcomponents/Spatial.h"
#include "../entitysystem/defaultcomponents/Graphics.h"
#include "../entitysystem/defaultsystems/Graphics.h"
#include "../entitysystem/defaultsystems/Input.h"
#include "../entitysystem/defaultsystems/Testing.h"
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
		entityManager.registerSystem(new Input());
		entityManager.registerSystem(new Test_Changepos());
		entityManager.registerSystem(new Test_Movement());
		entityManager.registerSystem(new Camera_Movement());

		// Axis
		entityManager.newEntity(Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 1.0f, 0.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 0.0f, 1.0f, 0.0f }, math::vec4f{ 0.0f, 1.0f, 0.0f, 1.0f } });
		entityManager.newEntity(Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec4f{ 0.0f, 0.0f, 1.0f, 1.0f } });

		// Generate the scene
		entityManager.newEntity(Line_Component{ math::vec3f{ 3.0f, -3.0f, 0.0f }, math::vec3f{ 3.0f, 3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(Line_Component{ math::vec3f{ -3.0f, -3.0f, 0.0f }, math::vec3f{ 3.0f, -3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(Line_Component{ math::vec3f{ 3.0f, 3.0f, 0.0f }, math::vec3f{ -3.0f, 3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(Line_Component{ math::vec3f{ -3.0f, 3.0f, 0.0f }, math::vec3f{ -3.0f, -3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });

		float speed = 1.5f;

		size_t countPoints = 10000;
		for (size_t i = 0; i < countPoints; i++)
		{
			float angle = math::toRadians(((float)rand() / (float)RAND_MAX) * 360.0f);
			entityManager.newEntity(Point_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f } }, Position_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f } }, Velocity_Component{ math::vec3f{ sin(angle) * speed, cos(angle) * speed, 0.0f } });
		}

		size_t countSprites = 0;//50*50;
		for (size_t i = 0; i < sqrt(countSprites); i++)
			for (size_t j = 0; j < sqrt(countSprites); j++)
				entityManager.newEntity(
					Sprite_Component{ "testSheet1", (i * j) % 8, 6.0f / (float)sqrt(countSprites) }, 
					Position_Component{ 
						math::vec3f{ 
						(6.0f / (float)sqrt(countSprites)) * i - (3) + (6.0f / (float)sqrt(countSprites)) / 2 , 
						(6.0f / (float)sqrt(countSprites)) * j - (3) + (6.0f / (float)sqrt(countSprites)) / 2, 
						-0.01f } });
	
		entityManager.newEntity(Camera_Component(FOV, ASPECT_RATIO, NEAR, FAR));
	}


	void WorldScene::update(const double &dt)
	{
		entityManager.update(dt);
	}
}