#include "Scene.h"
#include "../entities/Entity.h"

namespace abyssengine {
	Scene::~Scene()
	{
	}
	Camera* Scene::getCamera()
	{
		return camera;
	}

	EntityManager& Scene::getEntityManager()
	{
		return entityManager;
	}

}