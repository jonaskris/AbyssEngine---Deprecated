#pragma once
#include "GComponent.h"
#include "../../Entity.h"
#include "../../../graphics/TextureAtlas.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"

namespace abyssengine {
	class PComponent;
	class GLComponent : public GComponent
	{
	public:
		GLComponent();
		GLComponent(const math::vec3& vertex1, const math::vec3& vertex2);
		GLComponent(const math::vec3& vertex1, const math::vec3& vertex2, const math::vec4& color);
		GLComponent(const math::vec3& vertex1, const math::vec3& vertex2, const math::vec4& color1, const math::vec4& color2);

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
		};

		void setVertex(short i, math::vec3 vertex);
		void setColor(short i, math::vec4 color);
		math::vec3 getVertex(short i);
		math::vec4 getColor(short i);

		FrustumInfo getFrustumInfo();
	private:

		math::vec3 vertices[2] = {
			math::vec3(0.0f, 0.0f, 0.0f),
			math::vec3(1.0f, 1.0f, 1.0f)
		};

		math::vec4 colors[2]
		{
			math::vec4(1.0f, 0.0f, 1.0f, 1.0f),
			math::vec4(1.0f, 0.0f, 1.0f, 1.0f)
		};
	};
}