#pragma once
#include "GComponent.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"
#include <string>

namespace abyssengine {
	class GTComponent : public GComponent
	{
	public:
		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
			math::vec2 uv;
		};

		GTComponent(size_t fontId, float fontSize, std::string string);
		~GTComponent();

		FrustumInfo getFrustumInfo();

		void setPosition(math::vec3 position);
		void setScale(math::vec3 scale);
		void setColor(short i, math::vec4 color);

		math::vec3 getPosition();
		math::vec2 getScale();
		math::vec4* getColors();
		std::string getString();
		char* getChars();
		size_t getCharCount();
		size_t getFontId();
		float getFontSize();

		bool operator < (const GTComponent& other) const
		{
			return (fontId < other.fontId);
		}

	private:
		size_t fontId;
		float fontSize;
		std::string string;

		math::vec3 position = math::vec3(0.0f, 0.0f, 0.0f);
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