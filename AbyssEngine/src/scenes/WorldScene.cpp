#include "WorldScene.h"
#include "../math/linalg.h"
#include "../resources/resourcetypes/Texture.h"
#include "../entitysystem/defaultcomponents/Spatial.h"
#include "../entitysystem/defaultcomponents/Graphics.h"
#include "../entitysystem/defaultsystems/Graphics.h"
#include "../entitysystem/defaultsystems/Input.h"
#include "../entitysystem/defaultsystems/Testing.h"
#include "../resources/resourcemanager/ResourceManager.h"
#include "../Defines.h"
#include "../math/semantics/Time.h"

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
		entityManager.registerSystem(new entitysystem::MouseInput());
		entityManager.registerSystem(new entitysystem::KeyboardInput());
		//entityManager.registerSystem(new entitysystem::Test_Changepos());
		//entityManager.registerSystem(new entitysystem::Test_Movement());
		entityManager.registerSystem(new entitysystem::Camera_Rotation_Control());
		entityManager.registerSystem(new entitysystem::Camera_Position_Control());

		// Axis
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 1.0f, 0.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 0.0f, 1.0f, 0.0f }, math::vec4f{ 0.0f, 1.0f, 0.0f, 1.0f } });
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f }, math::vec3f{ 0.0f, 0.0f, 1.0f }, math::vec4f{ 0.0f, 0.0f, 1.0f, 1.0f } });
		
		// Generate the scene
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ 3.0f, -3.0f, 0.0f }, math::vec3f{ 3.0f, 3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ -3.0f, -3.0f, 0.0f }, math::vec3f{ 3.0f, -3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ 3.0f, 3.0f, 0.0f }, math::vec3f{ -3.0f, 3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		entityManager.newEntity(entitysystem::Line_Component{ math::vec3f{ -3.0f, 3.0f, 0.0f }, math::vec3f{ -3.0f, -3.0f, 0.0f }, math::vec4f{ 1.0f, 0.0f, 0.0f, 1.0f } });
		
		float speed = 1.5f;
		
		//size_t countPoints = 10000;
		//for (size_t i = 0; i < countPoints; i++)
		//{
		//	float angle = math::toRadians(((float)rand() / (float)RAND_MAX) * 360.0f);
		//	entityManager.newEntity(Point_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f}, math::vec4f{ 1.0f, 1.0f, 1.0f, 1.0f } }, Position_Component{ math::vec3f{ 0.0f, 0.0f, 0.0f } }, Velocity_Component{ math::vec3f{ sin(angle) * speed, cos(angle) * speed, 0.0f } });
		//}
		
		resources::TextureAtlas* textureAtlas = resources::ResourceManager::getInstance()->getResource<resources::TextureAtlas>("testSheet1.texa");

		/*
		math::vec3f{ 
						(6.0f / (float)sqrt(countSprites)) * i - (3) + (6.0f / (float)sqrt(countSprites)) / 2 , 
						(6.0f / (float)sqrt(countSprites)) * j - (3) + (6.0f / (float)sqrt(countSprites)) / 2, 
						-0.01f } 
		*/

		//entityManager.newEntity(
		//	Sprite_Component{ textureAtlas, 0, 1.0f },
		//	Transform_Component{ math::Translation{ math::vec3f{0.0f, 0.0f, 0.0f}} });

		size_t countSprites = 5*5;
		for (size_t i = 0; i < sqrt(countSprites); i++)
			for (size_t j = 0; j < sqrt(countSprites); j++)
				entityManager.newEntity(
					entitysystem::Sprite_Component{ textureAtlas, i * j, 6.0f / (float)sqrt(countSprites) },
					entitysystem::Transform_Component{ math::Translation{ math::vec3f{(6.0f / (float)sqrt(countSprites)) * i - (3) + (6.0f / (float)sqrt(countSprites)) / 2 , (6.0f / (float)sqrt(countSprites)) * j - (3) + (6.0f / (float)sqrt(countSprites)) / 2, -0.01f } } });
	
		entityManager.newEntity(entitysystem::Camera_Component(), entitysystem::Position_Component(math::vec3f(0.0f, 0.0f, 3.0f)));
	}


	void WorldScene::update(const math::Time& time)
	{
		entityManager.update(time);
	}
}