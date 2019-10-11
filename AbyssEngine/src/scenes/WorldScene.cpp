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

	//struct Orbit_Component : public entitysystem::Component<Orbit_Component>
	//{
	//	size_t entityIdOrbitTarget;
	//	float orbitVelocityDegrees;
	//
	//	Orbit_Component(const size_t& entityIdOrbitTarget, const float& orbitVelocityDegrees = 0.1f)
	//		: entityIdOrbitTarget(entityIdOrbitTarget), orbitVelocityDegrees(orbitVelocityDegrees) {};
	//};
	//
	//class Orbit_System : public entitysystem::System<Orbit_Component, entitysystem::Position_Component>
	//{
	//private:
	//	void update(const math::Time& time) override
	//	{
	//		updateEntities(time);
	//	}
	//
	//	void updateEntity(const math::Time& time, entitysystem::UnitGroup& units) override
	//	{
	//		Orbit_Component& orbit = units.get<Orbit_Component>().first[0];
	//		entitysystem::Position_Component& position = units.get<entitysystem::Position_Component>().first[0];
	//
	//		entitysystem::Position_Component& orbitTargetPosition = entityManager->getUnits<entitysystem::Position_Component>(orbit.entityIdOrbitTarget).first[0];
	//		
	//		position.position.vec -= orbitTargetPosition.position.vec;
	//		position.position.vec = math::toVec3f(math::mat4f::rotate(orbit.orbitVelocityDegrees, math::vec3f(0.0f, 0.0f, 1.0f)) * math::toVec4f(position.position.vec, 1.0f));
	//		position.position.vec += orbitTargetPosition.position.vec;
	//	}
	//};

	void WorldScene::generateScene()
	{
		using namespace entitysystem;

		auto resourcemanager = resources::ResourceManager::getInstance();

		// Generate resources
		math::Icosahedron::generate(4);

		// Register systems.
		entityManager.registerSystem(new MouseInput());
		entityManager.registerSystem(new KeyboardInput());
		entityManager.registerSystem(new Camera_Rotation_Control());
		entityManager.registerSystem(new Camera_Position_Control());
		entityManager.registerSystem(new Transform_Updater());
		//entityManager.registerSystem(new Orbit_System());

		// Create entities
			// Skybox
				entityManager.newEntity(																			/// Stars
					entitysystem::Transform_Component(
						math::Position(math::vec3f(0.0f, 0.0f, 0.0f)),
						math::Scale(math::vec3f(10.0f, 10.0f, 10.0f))
					),
					Mesh_Component("generated/icosahedron:3"),														// Sphere mesh
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Space.cm")->getTextureID())	// Cubemap texture
				);
			// Planets
				size_t sunId =
				entityManager.newEntity(																			/// Sun
					entitysystem::Transform_Component(math::Position(math::vec3f(0.0f, 0.0f, 0.0f))),
					Mesh_Component("generated/icosahedron:3", true),												// Sphere mesh (true: flip normals)
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Sun.cm")->getTextureID())	// Cubemap texture
				);
								
				size_t earthId =
				entityManager.newEntity(																			/// Earth
					entitysystem::Transform_Component(
						math::Position(math::vec3f(2.0f, 0.0f, 0.0f)),
						math::Rotation(math::vec3f(0.0f, 0.0f, 1.0f), 90.0f),
						math::RelativeTransform(sunId, math::RelativeTransform::Type::POSITION)
					),
					Mesh_Component("generated/icosahedron:3"),														// Sphere mesh
					Texture_Component(resourcemanager->getResource<resources::Cubemap>("Earth.cm")->getTextureID())// Cubemap texture
					//Orbit_Component(sunId),																		// Orbit around sun
					//Relative_Component(sunId)
				);

				//size_t moonId =
				//entityManager.newEntity(																			/// Moon
				//	Position_Component(math::vec3f(6.0f, 0.0f, 0.0f)),												// Position
				//	Scale_Component(math::vec3f(0.1f)),																// Scale
				//	Mesh_Component("generated/icosahedron:3"),														// Sphere mesh
				//	Texture_Component(resourcemanager->getResource<resources::Cubemap>("Moon.cm")->getTextureID()), // Cubemap texture
				//	Orbit_Component(earthId),																		// Orbit around earth
				//	Relative_Component(earthId)
				//);
			// Camera
				entityManager.newEntity(
					entitysystem::Camera_Component(), 
					entitysystem::Transform_Component(math::Position(math::vec3f(0.0f, 0.0f, 3.0f))));
				//entityManager.newEntity(Target_Camera(math::vec3f(-7.0f, 0.0f, 0.0f), moonId));
	}
}