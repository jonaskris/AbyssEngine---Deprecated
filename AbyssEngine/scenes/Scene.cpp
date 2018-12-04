#include "Scene.h"
#include "../entities/Entity.h"

Scene::~Scene()
{
}

std::vector<Entity*>& Scene::getEntities()
{
	return entities;
}

Camera* Scene::getCamera()
{
	return camera;
}

void Scene::addEntity(Entity* e)
{
	entities.push_back(e);
}

void Scene::addEntities(std::vector<Entity*>& entities)
{
	for (size_t i = 0; i < entities.size(); i++) 
	{
		addEntity(entities.back());
		entities.pop_back();
	}
}