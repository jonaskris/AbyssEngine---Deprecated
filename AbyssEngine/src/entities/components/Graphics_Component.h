#pragma once
#include <string>

#include "Component.h"
#include "Position_Component.h"

#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"

namespace abyssengine {

	//! Base of graphics components, specialization of component
	struct Graphics_Component : public Component
	{
		enum types { Sprite, Line, Point, Text, MAX };
		types type;

		struct FrustumInfo
		{
			float biggestEnclosingRadius;
			math::vec3 center;
		} frustumInfo;

	protected:
		Graphics_Component(types type, unsigned int entityId) : Component(Component::types::Graphics, entityId)
		{
			this->type = type;
		};
	};

	//! Sprite component, specialization of graphics component
	struct Graphics_Sprite_Component : public Graphics_Component
	{
		Graphics_Sprite_Component(unsigned int entityId) : Graphics_Component(Graphics_Component::types::Sprite, entityId) {};

		unsigned short textureID;
		unsigned short atlasID;

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;
		} vertices[4];
	};

	//! Line component, specialization of graphics component
	struct Graphics_Line_Component : public Graphics_Component
	{
		Graphics_Line_Component(unsigned int entityId) : Graphics_Component(Graphics_Component::types::Line, entityId) {};

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
		} vertices[2];
	};

	//! Point component, specialization of graphics component
	struct Graphics_Point_Component : public Graphics_Component
	{
		Graphics_Point_Component(unsigned int entityId) : Graphics_Component(Graphics_Component::types::Point, entityId) {};

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
		} vertex;
	};

	//! Text component, specialization of graphics component
	struct Graphics_Text_Component : public Graphics_Component
	{
		Graphics_Text_Component(unsigned int entityId) : Graphics_Component(Graphics_Component::types::Text, entityId) {};

		unsigned short fontId;
		float fontSize;
		std::string string; // Change to char array with fixed/max size

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;
		} vertices[4];
	};
}