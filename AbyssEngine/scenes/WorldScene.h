#pragma once
#include <vector>
#include "Scene.h"
#include "../graphics/Camera.h"

class Entity;

class WorldScene: public Scene
/*
  |	WorldScene:
  | WS is created upon leaving the GUI and starting the game. It populates itself with entities using a WorldGen class.
*/
{
public:
	WorldScene();
	~WorldScene();
	void generateScene();

	void update(double deltaTime);
};

