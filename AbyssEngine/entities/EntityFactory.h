#pragma once
#include <vector>
#include "Entity.h"
#include "components/Component.h"
#include "components/CComponent.h"
#include "components/PComponent.h"
#include "components/SComponent.h"
#include "components/gComponent/GComponent.h"
#include "components/gComponent/GSSComponent.h"
#include "components/gComponent/GTComponent.h"
#include "../graphics/TextureAtlas.h"


namespace EntityFactory
{
	enum entityType { BASIC };

	void createEntity(entityType type)
	{
		std::vector<Component*> components;
		switch (type)
		{
		case BASIC:
			
			/*PComponent* nullpointer = 0;
			components.push_back(new GSSComponent(*nullpointer, TextureAtlas::getAtlas(TextureAtlas::Atlas::TESTSHEET)->getTextureID, 0));

			return new Entity(components);*/
			break;
		}
	}
};

