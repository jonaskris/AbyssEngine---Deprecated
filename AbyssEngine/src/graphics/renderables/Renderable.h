#pragma once
#include "../../math/Linalg.h"
#include "../../entitysystem/components/Component.h"

namespace abyssengine {
	namespace graphics
	{
		struct RenderableBase
		{
			virtual math::mat4f& getTransform() = 0;
		};

		template <typename RenderableType>
		struct Renderable : public entitysystem::Component<RenderableType>
		{
			friend class Renderer;
		protected:
			math::mat4f transform;

			template <typename Transform>
			void unpackTransforms(const Transform& transform)
			{
				this->transform *= transform;
			}

			template <typename Transform, typename... Transforms>
			void unpackTransforms(const Transform& transform, const Transforms& ... transforms)
			{
				this->transform *= transform;
				unpackTransforms(transforms...);
			}

			template <typename... Transforms>
			Renderable(const Transforms& ... transforms) { unpackTransforms(transforms...); }

			Renderable() : transform(math::mat4f::identity()) {}

		public:
			math::mat4f& getTransform() override { return transform; }
		};
	}
}