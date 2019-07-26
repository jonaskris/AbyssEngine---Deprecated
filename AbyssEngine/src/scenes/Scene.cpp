#include "Scene.h"

namespace abyssengine {
	Scene::~Scene()
	{
	}
	//Camera* Scene::getCamera()
	//{
	//	return camera;
	//}

	entitysystem::EntityManager* Scene::getEntityManager()
	{
		return &entityManager;
	}
}