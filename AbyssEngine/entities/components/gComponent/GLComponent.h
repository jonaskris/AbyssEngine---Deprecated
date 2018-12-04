#pragma once
#include "GComponent.h"
#include "../../Entity.h"
#include "../../../graphics/TextureAtlas.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"

class PComponent;

class GLComponent : public GComponent
{
public:
	GLComponent();
	GLComponent(const vec3& vertex1, const vec3& vertex2);

	struct VertexData {
		vec3 vertex;
		vec4 color;
	};

	vec3 vertices[2] = { 
		vec3(0.0f, 0.0f, 0.0f),
		vec3(1.0f, 1.0f, 1.0f) 
	};

	vec4 colors[2]
	{
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec4(1.0f, 0.0f, 1.0f, 1.0f)
	};
};

