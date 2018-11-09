#pragma once
#include "GComponent.h"
#include "../../../math/mat4.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"
#include "../PComponent.h"
#include "../../../graphics/TextureAtlas.h"

class GSSComponent : public GComponent
{
public:
	struct VertexData {
		vec3 vertex;
		vec4 color;
		vec2 uv;
	};

	GSSComponent(PComponent* pComponent, TextureAtlas::Atlas atlas, unsigned short textureID);
	vec3 position;
	vec3 rotation;
	vec2 scale;
	vec4 color[4]
	{
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	};

	std::vector<vec2> uv;

	void setAtlas(TextureAtlas::Atlas atlas, unsigned short textureID);
	void setTextureID(unsigned short textureID);
private:
	unsigned short textureID;
	TextureAtlas::Atlas atlas;

	void updateUV();
	PComponent* pComponent;
};