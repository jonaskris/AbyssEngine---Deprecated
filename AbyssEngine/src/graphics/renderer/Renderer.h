#pragma once
#include <vector>
#include <utility>
#include <optional>
#include "../../math/Linalg.h"

namespace abyssengine {
	namespace graphics {
		class Renderable
		{
			class Mesh {
				class VBOElement
				{
					std::vector<math::vec3f> vertices;

					VBOElement(const size_t& count) { vertices.resize(count); }

					void populate(/*File*/) {};
				};

				class IBOElement
				{
					std::vector<size_t> indices;

					IBOElement(const size_t& count) { indices.resize(count); }

					void populate(/*File*/) {};
				};

				class Material
				{

				};
			};
			std::vector<Mesh> meshes;
		};

		class Renderer
		{

		};
	}
}