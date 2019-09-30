#pragma once

namespace abyssengine {
	/*
		RenderableHandles are stored in components where it can be referred to when needed.
	*/
	template <typename RenderableType>
	struct RenderableHandle
	{
	private:
		Renderable<RenderableType>* renderable;
	public:
		Renderable<RenderableType>& getRenderable() { return *renderable; }

		RenderableHandle(Renderable<RenderableType>* renderable) : renderable(renderable) { };
		~RenderableHandle() {};
	};
}