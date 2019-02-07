#pragma once
#include "GComponent.h"
#include "../../Entity.h"
#include "../../../graphics/TextureAtlas.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"

namespace abyssengine {
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
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;
		};

		GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID);
		GSSComponent(TextureAtlas::Atlas atlas, unsigned short textureID, math::vec2 scale);

		std::vector<math::vec2> uv;

		void setAtlas(TextureAtlas::Atlas atlas, unsigned short textureID);
		void setTextureID(unsigned short textureID);

		void setPosition(math::vec3 position);
		void setRotation(math::vec3 rotation);
		void setScale(math::vec3 scale);
		void setColor(short i, math::vec4 color);

		math::vec3 getPosition();
		math::vec3 getRotation();
		math::vec2 getScale();
		math::vec4 getColor(short i);
		math::vec4* getColors();
	private:
		math::vec3 position = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 rotation = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec2 scale = math::vec2(1.0f, 1.0f);
		math::vec4 colors[4]
		{
			math::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			math::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			math::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			math::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		};
	};
}