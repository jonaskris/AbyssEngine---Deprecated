#pragma once
#include <vector>
#include "../graphics/shaders/Shader.h"

class Entity;
class Shader;

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