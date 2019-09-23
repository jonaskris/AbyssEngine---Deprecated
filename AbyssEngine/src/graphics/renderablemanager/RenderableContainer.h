//#pragma once
//#include <utility>
//#include <vector>
//#include "../renderable/Renderable.h"
//#include "../../utils/TypeIdentifier.h"
//
//namespace abyssengine {
//	namespace graphics {
//		class RenderableContainerBase
//		{
//		private:
//			virtual void addToInsertionQueue(RenderableBase const* renderable) = 0;
//		
//		public:
//			virtual size_t getRenderableTypeIdentifier() = 0;
//
//			/*
//				Inserts Renderables from queue;
//			*/
//			virtual void insertFromQueue() = 0;
//
//			template <typename RenderableType>
//			RenderableHandle<RenderableType> insertRenderable(const RenderableType& renderable)
//			{
//				static_assert(std::is_base_of<RenderableBase, RenderableType>::value, "RenderableType must be derived from RenderableBase!");
//
//			}
//
//			template <typename RenderableType>
//			bool storesRenderableType()
//			{
//				static_assert(std::is_base_of<RenderableBase, RenderableType>::value, "RenderableType must be derived from RenderableBase!");
//				return getIdentifier() == RenderableType::getIdentifier();
//			}
//			
//			/*
//				Returns the identifier of the RenderableType the RenderableContainer stores.
//			*/
//			virtual size_t getIdentifier() const = 0;
//
//			virtual size_t size() const = 0;
//		};
//
//		template <typename RenderableType>
//		class RenderableContainer
//		{
//			static_assert(std::is_base_of<RenderableBase, RenderableType>::value, "RenderableType must be derived from RenderableBase!");
//
//		private:
//			std::vector<RenderableType> insertionQueue;	// To avoid invalidating iterators during system updates, 
//														// and reduces allocation by inserting in bunches.
//		public:
//			virtual void render() = 0;
//
//			size_t getRenderableTypeIdentifier() override { return utils::TypeIdentifier<RenderableType>::getIdentifier(); };
//		};
//	}
//}