#pragma once
#include "GComponent.h"
#include "../../Entity.h"
#include "../../../graphics/TextureAtlas.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"

class PComponent;

class GSSComponent : public GComponent
{
private:
	unsigned short textureID;
	TextureAtlas::Atlas atlas;
	void updateUV();
	FrustumInfo getFrustumInfo();
public:
	struct VertexData {
		vec3 vertex;
		vec4 color;
		vec2 uv;
	};

	GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID);
	GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID, vec2 scale);

	std::vector<vec2> uv;

	void setAtlas(TextureAtlas::Atlas atlas, unsigned short textureID);
	void setTextureID(unsigned short textureID);

	void setPosition(vec3 position);
	void setRotation(vec3 rotation);
	void setScale(vec3 scale);
	void setColor(short i, vec4 color);

	vec3 getPosition();
	vec3 getRotation();
	vec2 getScale();
	vec4 getColor(short i);
	vec4* getColors();
private:
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
	vec2 scale = vec2(1.0f, 1.0f);
	vec4 colors[4]
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f)
	};
};