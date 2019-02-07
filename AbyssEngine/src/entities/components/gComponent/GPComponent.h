#pragma once
#include "GComponent.h"
#include "../../Entity.h"
#include "../../../graphics/TextureAtlas.h"
#include "../../../math/vec4.h"
#include "../../../math/vec3.h"
#include "../../../math/vec2.h"

namespace abyssengine {
	class PComponent;
	class GPComponent : public GComponent
	{
	public:
		GPComponent();
		GPComponent(const math::vec3& vertex);
		GPComponent(const math::vec3& vertex1, const math::vec4& color);

		struct VertexData {
			math::vec3 vertex;
			math::vec4 color;
		};

		void setVertex(math::vec3 vertex);
		void setColor(math::vec4 color);
		math::vec3 getVertex();
		math::vec4 getColor();

		FrustumInfo getFrustumInfo();
	private:
		math::vec3 vertex = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec4 color = math::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	};
}