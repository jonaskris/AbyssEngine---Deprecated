#include <vector>
#include "CComponent.h"
#include "gComponent/GLComponent.h"
#include "../../math/geometry/Shape.h"
#include "../../math/vec3.h"

namespace abyssengine {
	CComponent::CComponent(Shape::shape shape, math::vec3 scale) : Component(Component::componentType::CComponentType)
	{
		this->vertices = Shape::getVertices(shape);
		this->indices = Shape::getIndices(shape);

		for (size_t i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i] = this->vertices[i] * scale;
		}
	}

	std::vector<GLComponent*> CComponent::getGLComponents()
	{
		std::vector<GLComponent*> returnVector;

		for (size_t i = 0; i < indices.size() / 2; i++)
		{
			returnVector.push_back(new GLComponent(vertices[indices[i * 2]], vertices[indices[i * 2 + 1]]));
			returnVector.back()->bindPComponent(pComponent);
		}

		return returnVector;
	}

	void CComponent::bindPComponent(PComponent* pComponent)
	{
		this->pComponent = pComponent;
	}

	void CComponent::collided(CComponent* other)
	{
	}
}