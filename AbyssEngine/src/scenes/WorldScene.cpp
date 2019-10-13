#include "WorldScene.h"
#include "../math/linalg.h"
#include "../resources/resourcetypes/Texture.h"
#include "../entitysystem/defaultcomponents/Spatial.h"
#include "../entitysystem/defaultcomponents/Graphics.h"
#include "../entitysystem/defaultsystems/Graphics.h"
#include "../entitysystem/defaultsystems/Input.h"
#include "../entitysystem/defaultsystems/Testing.h"
#include "../entitysystem/defaultsystems/Spatial.h"
#include "../math/Geometry.h"
#include "../resources/resourcemanager/ResourceManager.h"
#include "../Defines.h"
#include "../math/semantics/Time.h"
#include "../resources/resourcetypes/Cubemap.h"

namespace abyssengine {

	struct Orbit_Component : public entitysystem::Component<Orbit_Component>
	{
		float orbitSpeed;

		Orbit_Component(const float& orbitSpeed) : orbitSpeed(orbitSpeed) {};
	};

class Orbit_System : public entitysystem::System<entitysystem::Transform_Component, Orbit_Component>
{
private:
	void update(const math::Time& time) override
	{
		updateEntities(time);
	}

	void updateEntity(const math::Time& time, entitysystem::UnitGroup& units) override
	{
		entitysystem::Transform_Component& transform = units.get<entitysystem::Transform_Component>().first[0];
		Orbit_Component& orbit = units.get<Orbit_Component>().first[0];

		if (transform.transforms.size() > 2)
			transform.transforms.at(2) = math::mat4f::rotate(orbit.orbitSpeed, math::vec3f(0.0f, 0.0f, 1.0f)) * transform.transforms.at(2);
	}
};

	void WorldScene::generateScene()
	{
		using namespace entitysystem;

		auto resourcemanager = resources::ResourceManager::getInstance();

		// Generate resources
		math::Icosahedron::generate(4); // Generates sphere mesh used for planets and skybox.

		// Register systems
		entityManager.registerSystem(new MouseInput());
		entityManager.registerSystem(new KeyboardInput());
		entityManager.registerSystem(new Camera_Rotation_Control());
		entityManager.registerSystem(new Camera_Position_Control());
		entityManager.registerSystem(new Orbit_System());
		entityManager.registerSystem(new Transform_Updater());

		// Create entities
			// Skybox
				entityManager.newEntity(																		
					entitysystem::Transform_Component(
						math::Position(math::vec3f(0.0f, 0.0f, 0.0f)),
						math::Scale(math::vec3f(10.0f, 10.0f, 10.0f))
					),
					Mesh_Component("generated/icosahedron:3"),
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Space.cm")->getTextureID())
				);
			// Planets
				size_t sunId =
				entityManager.newEntity(
					entitysystem::Transform_Component(
						math::Scale(math::vec3f(0.5f)),
						math::Position(math::vec3f(0.0f, 0.0f, 0.0f))
					),
					Mesh_Component("generated/icosahedron:3", true),												
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Sun.cm")->getTextureID())
				);
								
				size_t earthId =
					entityManager.newEntity(																			
					entitysystem::Transform_Component(
						math::Scale(math::vec3f(0.5f)),
						math::Position(math::vec3f(3.0f, 0.0f, 0.0f)),
						math::Rotation(math::vec3f(0.0f, 0.0f, 1.0f), 0.0f),
						math::RelativeTransform(sunId, math::RelativeTransform::POSITION)
					),
					Mesh_Component("generated/icosahedron:3"),														
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Earth.cm")->getTextureID()),
					Orbit_Component(0.1f)
				);

				size_t moonId =
				entityManager.newEntity(																		
					entitysystem::Transform_Component(
						math::Scale(math::vec3f(0.2f)),
						math::Position(math::vec3f(1.0f, 0.0f, 0.0f)),
						math::Rotation(math::vec3f(0.0f, 0.0f, 1.0f), 0.0f),
						math::RelativeTransform(earthId, math::RelativeTransform::POSITION)
					),
					Mesh_Component("generated/icosahedron:3"),														
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Moon.cm")->getTextureID()), 
					Orbit_Component(0.2f)
				);
			// Camera
				entityManager.newEntity(Target_Camera(math::vec3f(-5.0f, 0.0f, 0.0f), moonId));
	}
}

//entityManager.newEntity(
//	entitysystem::Camera_Component(), 
//	entitysystem::Transform_Component(math::Position(math::vec3f(0.0f, 0.0f, 3.0f))));