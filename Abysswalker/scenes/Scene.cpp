#include "Scene.h"

Scene::~Scene()
{
	if (shader != 0) {
		delete shader;
	}
}

std::vector<Entity*>* Scene::getEntities()
{
	return &entities;
}

void Scene::addEntity(Entity* e)
{
	entities.push_back(e);
}

void Scene::addEntities(std::vector<Entity*>& entities)
{
	for (int i = 0; i < entities.size(); i++) {
		addEntity(entities.back());
		entities.pop_back();
	}
}

Shader* Scene::getShader()
{
	return shader;
}

void Scene::setShader(Shader* shader)
{
	this->shader = shader;
}
