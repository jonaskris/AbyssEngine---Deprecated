#pragma once
#include "../../math/mat4.h"
#include "../../entitysystem/units/UnitGroup.h"

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
		virtual void begin(const math::mat4& perspectiveViewMatrix) = 0;

		/*
			Submits a UnitGroup to be rendered.
		*/
		virtual void submit(UnitGroup& unitGroup) = 0;

		/*
			Draws submitted graphics components.
		*/
		virtual void end() = 0;
	};
}