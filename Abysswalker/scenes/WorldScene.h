#pragma once
#include "Scene.h"

class WorldScene: public Scene
/*
  |	WorldScene:
  | WS is created upon leaving the GUI and starting the game. It populates itself with entities using a WorldGen class.
*/
{
public:
	WorldScene();
	~WorldScene();
};

