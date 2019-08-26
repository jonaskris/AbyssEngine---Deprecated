#include "Scene.h"

namespace abyssengine {
	Scene::~Scene()
	{
	}

	entitysystem::EntityManager* Scene::getEntityManager()
	{
		return &entityManager;
	}
}