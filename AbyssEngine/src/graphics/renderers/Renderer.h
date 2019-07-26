#pragma once
#include "../../math/linalg.h"
#include "../../entitysystem/units/UnitGroup.h"
#include "../../entitysystem/entitymanager/EntityManager.h"
#include "../../entitysystem/entitymanager/EachCallable.h"

namespace abyssengine
{
	/*
		Renders submitted graphics components.
		Any one renderer uses only one program (Set of shaders). 
	*/
	class Renderer
	{
	public:
		/*
			Performs necessary one time operations before rendering.
		*/
		virtual void begin(const math::mat4f& perspectiveViewMatrix) = 0;

		virtual void submitUnits(entitysystem::EntityManager* entitymanager) = 0;

		/*
			Submits a UnitGroup to be rendered.
		*/
		virtual void submit(entitysystem::UnitGroup& unitGroup) = 0;

		/*
			Draws submitted graphics components.
		*/
		virtual void end() = 0;
	};
}