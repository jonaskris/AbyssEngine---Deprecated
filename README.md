The project has been abandoned indefinitely, and is instead developed under the repository with the same name in the Rust language.
Motivation for abandonment is to develop the project from ground-up with multithreading in mind.

# AbyssEngine

The purpose of the project is to gain experience with creating a fully fleshed out
project that can give a broader understanding of programming.

Dependencies: GLEW, GLFW, SOIL, FreeType and Nlohmann's JSON library.

## Features
* **Graphics**
    * Deferred rendering with OpenGL.
* **Entity-Component-System (ECS)**
    * A Data-Oriented architectural pattern that favours composition over inheritance.
    * Entities are solely defined by the components it exists of, and are identified by an entityId which its components stores.
    * Components are logicless data objects stored continuously in memory in the entitymanager.
    * Events are components that have a limited lifetime and can be used to broadcast information.
    * [More information](https://github.com/jonaskris/EntitySystem)
* **Resource Loading**
    * Resources are all loaded on program start and kept in memory for the entirety of the session.
    * Supports setting default resources per type that are returned if the requested resource was not found.
    * Textures are loaded using [SOIL](https://www.lonesock.net/soil.html).
    * Fonts are loaded using [FreeType](https://www.freetype.org/).
    * JSON is loaded using [nlohmann's JSON library](https://github.com/nlohmann/json).
* **Input**
    * Keyboard and mouse.
    * ~~Controller~~
* **~~Collision & Physics~~**
    * ~~Broad-phase~~
    * ~~Narrow-phase~~
* **~~Audio~~**
## Usage (Example scene)
<img src="Solar_system_scene.gif?raw=true" width="600px">

### Defining components:

```
struct Orbit_Component : public entitysystem::Component<Orbit_Component>
{
	float orbitSpeed;

	Orbit_Component(const float& orbitSpeed) : orbitSpeed(orbitSpeed) {};
};
```

### Defining systems:

```
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
```

### Setting up a scene:

```
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
```
