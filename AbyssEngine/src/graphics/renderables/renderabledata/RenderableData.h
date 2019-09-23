#pragma once

namespace abyssengine {
	namespace graphics {
		struct RenderableData
		{
		private:
			// Shared RenderableData is the same for every of that Renderable.
			bool shared;
		protected:
			RenderableData(const bool& shared) : shared(shared) {};
		public:
			bool getShared() const { return shared; }
		};
	}
}