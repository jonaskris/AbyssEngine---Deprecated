#pragma once
#include <utility>
#include "../../utils/TypeIdentifier.h"
#include "../components/Component.h"
#include "../../math/linalg.h"
#include "../../math/semantics/Transform.h"

namespace abyssengine {
	namespace entitysystem {
		struct Transform_Component : public Component<Transform_Component>
		{
			std::vector<std::pair<math::RelativeTransform, size_t>> relativeTransforms;	// Updates transforms at index
			std::vector<math::mat4f> transforms;

			template <typename Transform>
			void unpackRenderableOptions(const Transform& transform)
			{
				static_assert(std::is_base_of<math::Transform, Transform>::value, "Transform must be of type math::Transform!");

				if constexpr (std::is_base_of<math::RelativeTransform, Transform>::value) {
					transforms.push_back(math::mat4f::identity());
					relativeTransforms.push_back(std::pair<math::RelativeTransform, size_t>(transform, transforms.size() - 1));
				} else {
					transforms.push_back(transform.toMatrix());
				}
			}
		
			template <typename Transform, typename... Transforms>
			void unpackRenderableOptions(const Transform& transform, const Transforms& ... transforms)
			{
				static_assert(std::is_base_of<math::Transform, Transform>::value, "Transform must be of type math::Transform!");

				if constexpr (std::is_base_of<math::RelativeTransform, Transform>::value) {
					transforms.push_back(math::mat4f::identity());
					relativeTransforms.push_back(std::pair<math::RelativeTransform, size_t>(transform, this->transforms.size() - 1));
				} else {
					transforms.push_back(transform.toMatrix());
				}

				unpackRenderableOptions(transforms...);
			}
		
			template <typename... Transforms>
			Transform_Component(Transforms... transforms)
			{
				if constexpr (sizeof...(Transforms) > 0)
					unpackRenderableOptions(transforms...);
			};

			void update(EntityManager* entityManager)
			{
				for (std::pair<math::RelativeTransform, size_t>& transform : relativeTransforms)
				{
					Transform_Component& relativeTransform = entityManager->getUnits<Transform_Component>(transform.first.relativeEntityId).first[0];

					relativeTransform.update(entityManager);

					switch(transform.first.type)
					{
						case math::RelativeTransform::Type::POSITION:
							transforms[transform.second] = relativeTransform.toMatrix().decomposeToTranslation();
							break;
						case math::RelativeTransform::Type::ROTATION:
							transforms[transform.second] = relativeTransform.toMatrix().decomposeToRotation();
							break;
						case math::RelativeTransform::Type::SCALE:
							transforms[transform.second] = relativeTransform.toMatrix().decomposeToScale();
							break;
					}
				}
			}

			math::mat4f toMatrix()
			{
				math::mat4f returnMatrix = transforms[0];

				for (size_t i = 1; i < transforms.size(); i++)
					returnMatrix = transforms[i] * returnMatrix;
				return returnMatrix;
			}
		};
	}
}