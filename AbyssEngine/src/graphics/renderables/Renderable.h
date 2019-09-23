#pragma once
#include <utility>
#include <nlohmann/json.hpp>
#include "../renderer/Renderer.h"
#include "../../utils/TypeIdentifier.h"

namespace abyssengine {
	namespace graphics
	{
		/*
			RenderableHandles are stored in components where it can be referred to when needed.
		*/
		template <typename RenderableType>
		struct RenderableHandle : public utils::TypeIdentifier<RenderableType>
		{
		private:
			Renderable<RenderableType>* renderable;
		public:
			Renderable<RenderableType>& getRenderable() { return *renderable; }

			RenderableHandle(Renderable<RenderableType>* renderable) : renderable(renderable) { };
			~RenderableHandle() { Renderer::removeRenderable<RenderableType>(); };
		};

		/*
			Renderables are stored contiguously in RenderableContainer and can be referred to by
			its RenderableHandle.
		*/
		struct RenderableBase 
		{ 
			virtual size_t getRenderableTypeIdentifier() = 0;
		};

		template <typename RenderableType>
		struct Renderable : public utils::TypeIdentifier<RenderableType>
		{
			friend class Renderer;
		public:			
			size_t getRenderableTypeIdentifier() const override { return utils::TypeIdentifier<RenderableType>::getIdentifier(); }

			template <typename... Args>
			static RenderableHandle<RenderableType> newRenderable(const Args& ... args)
			{
				return Renderer::makeRenderable<RenderableType, Args...>(args...);
			}
		};
	}
}