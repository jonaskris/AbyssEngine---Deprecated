#pragma once
#include <GL/glew.h>
#include <vector>
#include "../resource/Resource.h"
#include "../resource/ResourceException.h"
#include "Texture.h"

namespace abyssengine {
	namespace resources {
		class MeshResource : public Resource<MeshResource>
		{
			friend class ResourceBase;
		private:
			math::Mesh mesh;

		public:
			MeshResource(const std::string& path, const math::Mesh& mesh) : Resource(path), mesh(mesh)
			{
				
			}			

			math::Mesh& getMesh() { return mesh; }
		};
	}
}