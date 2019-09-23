#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../renderable/Renderable.h"
#include "../renderable/RenderableStorageSpecifier.h"
#include "../../math/Linalg.h"

namespace abyssengine {
	namespace graphics {
		struct SpriteRenderable : public Renderable<SpriteRenderable>
		{
		private:
			GLuint textureId;
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
		public:
			template <typename... Transforms>
			SpriteRenderable(const GLuint& textureId, const Transforms&... transforms) : textureId(textureId)
			{
				unpackTransforms(transforms...);
			};
		};
	}
}