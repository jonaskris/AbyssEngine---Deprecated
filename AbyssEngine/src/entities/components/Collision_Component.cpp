#include "Collision_Component.h"
#include "../../math/geometry/Shape.h"
#include "../../math/mat4.h"
#include "../../math/vec4.h"
#include "../../math/vec3.h"

namespace abyssengine 
{
	void Collision_Component::applyAction(Collision_Component::VecAction& fa)
	{
		switch (fa.getType())
		{
		case SetScale:
			this->verticesValid = false;
			this->scale = fa.getData();
			break;
		case ChangeScale:
			this->verticesValid = false;
			this->scale += fa.getData();
			break;
		case SetRotation:
			this->verticesValid = false;
			this->rotation = fa.getData();
			break;
		case ChangeRotation:
			this->verticesValid = false;
			this->rotation += fa.getData();
			break;
		default:
			std::cout << "Tried applying an action to a Collision_Component, but the action type was not recognized!" << std::endl;
			break;
		}
	}

	bool Collision_Cube_Component::collided(const Collision_Component& other)
	{
		//if(!verticesValid)
		//	validateVertices();
		return false;
	}

	void Collision_Cube_Component::validateVertices()
	{
		this->verticesValid = true;

		math::mat4 rotationMatrix = math::mat4::rotation(1.0f, this->rotation);
		for (size_t i = 0; i < 8; i++)
		{
			this->vertices[i].vertex = math::vec3(rotationMatrix * math::vec4(Shape::cubeVertices[i] * this->scale, 0.0f));
		}
	}
}