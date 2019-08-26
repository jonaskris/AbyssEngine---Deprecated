#pragma once
#include <vector>
//#include "../graphics/shaders/Shader.h"
#include "../entitysystem/entitymanager/EntityManager.h"
#include "../math/semantics/Time.h"

namespace abyssengine {
	class Scene
	{
	protected:
		entitysystem::EntityManager entityManager;
	public:
		virtual ~Scene();

		virtual void update(const math::Time& time) = 0;

		entitysystem::EntityManager* getEntityManager();
	};
}