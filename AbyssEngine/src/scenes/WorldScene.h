#pragma once
#include <vector>
#include "Scene.h"
//#include "../graphics/Camera.h"
#include "../math/semantics/Time.h"

namespace abyssengine {
	class Entity;
	class WorldScene : public Scene
		/*
		  |	WorldScene:
		  | WS is created upon leaving the GUI and starting the game. It populates itself with entities using a WorldGen class.
		*/
	{
	public:
		WorldScene() { generateScene(); }
		~WorldScene() { };
		void generateScene();
	};
}