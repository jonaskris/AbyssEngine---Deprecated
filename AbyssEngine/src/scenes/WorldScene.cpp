#include "WorldScene.h"
#include "../math/linalg.h"
#include "../resources/resourcetypes/Texture.h"
#include "../entitysystem/defaultcomponents/Spatial.h"
#include "../entitysystem/defaultcomponents/Graphics.h"
#include "../entitysystem/defaultsystems/Graphics.h"
#include "../entitysystem/defaultsystems/Input.h"
#include "../entitysystem/defaultsystems/Testing.h"
#include "../math/Geometry.h"
#include "../resources/resourcemanager/ResourceManager.h"
#include "../Defines.h"
#include "../math/semantics/Time.h"
#include "../resources/resourcetypes/Cubemap.h"

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
		auto resourcemanager = resources::ResourceManager::getInstance();

		// Generate resources
		math::Icosahedron::generateFirst();
		math::Icosahedron::generate(1);
		math::Icosahedron::generate(2);
		math::Icosahedron::generate(3);
		math::Icosahedron::generate(4);

		// Register systems.
		entityManager.registerSystem(new entitysystem::MouseInput());
		entityManager.registerSystem(new entitysystem::KeyboardInput());
		entityManager.registerSystem(new entitysystem::Camera_Rotation_Control());
		entityManager.registerSystem(new entitysystem::Camera_Position_Control());
		entityManager.registerSystem(new entitysystem::Planet_Rotation());

		// Create entities
			// Camera
				entityManager.newEntity(entitysystem::Camera_Component(), entitysystem::Position_Component(math::vec3f(0.0f, 0.0f, 3.0f)));
			// Skybox
				entityManager.newEntity(																	/// Stars
					entitysystem::Mesh_Component(															// Skybox mesh				
						"generated/icosahedron:3",																// Icosahedron mesh
						resourcemanager->getResource<resources::Cubemap>("Space.cm")->getTextureID(),			// Cubemap
						math::vec3f(0.0f, 0.0f, 0.0f),															// Position
						math::vec3f(10.0f, 10.0f, 10.0f)));														// Scale
			// Planets
				entityManager.newEntity(																	/// Sun
					entitysystem::Mesh_Component(															// Planet mesh				
						"generated/icosahedron:3",																// Icosahedron mesh
						resourcemanager->getResource<resources::Cubemap>("Sun.cm")->getTextureID(),				// Cubemap
						math::vec3f(0.0f, 0.0f, 0.0f),															// Position
						math::vec3f(1.0f, 1.0f, 1.0f), true));													// Scale (True: Invert normals)

				entityManager.newEntity(																	/// Earth
					entitysystem::Mesh_Component(															// Planet mesh				
						"generated/icosahedron:3",																// Icosahedron mesh
						resourcemanager->getResource<resources::Cubemap>("Earth.cm")->getTextureID(),			// Cubemap
						math::vec3f(5.0f, 0.0f, 0.0f),															// Position
						math::vec3f(0.3f, 0.3f, 0.3f),															// Scale
						false,
						math::vec4f(0.0f, 0.0f, 1.0f, 0.0f)));

	}

	void WorldScene::update(const math::Time& time)
	{
		entityManager.update(time);
	}
}