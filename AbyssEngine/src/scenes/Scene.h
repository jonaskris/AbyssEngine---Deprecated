#pragma once
#include <vector>
#include "../graphics/shaders/Shader.h"
#include "../entitysystem/entities/EntityManager.h"

namespace abyssengine {
	//class Camera;

	class Scene
	{
	protected:
		//Camera* camera = NULL;
		EntityManager entityManager;
	public:
		virtual ~Scene();

		//Camera* getCamera();
		virtual void update(const double &dt) = 0;

		EntityManager* getEntityManager();
	};
}