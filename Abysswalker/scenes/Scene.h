#pragma once
#include "../entities/Entity.h"
#include "../graphics/shaders/Shader.h"
#include <vector>

class Scene
{
protected:
	std::vector<Entity*> entities;
	Shader* shader;
	void addEntity(Entity* e);
	void addEntities(std::vector<Entity*>& entities);
	Shader* getShader();
	void setShader(Shader* shader);

public:
	virtual ~Scene();

	std::vector<Entity*>* getEntities();
};