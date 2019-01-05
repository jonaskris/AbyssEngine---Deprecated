#pragma once
#include <vector>
#include "../graphics/shaders/Shader.h"

class Entity;
class Camera;

class Scene
{
protected:
	std::vector<Entity*> entities;
	Camera* camera;

	void addEntity(Entity* e);
	void addEntities(std::vector<Entity*>& entities);

public:
	virtual ~Scene();

	std::vector<Entity*>& getEntities();
	Camera* getCamera();
	virtual void update(double deltaTime) = 0;
};