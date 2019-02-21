#pragma once

namespace abyssengine {

	//! Base of all components
	struct Component
	{
		enum types { Collision, Graphics, Position, MAX };
	private:
		unsigned int entityId;
		types type;
	public:
		Component(Component::types type, unsigned int entityId)
		{ 
			this->entityId = entityId;
			this->type = type;
		}

		unsigned int getEntityId()
		{
			return this->entityId;
		}

		Component::types getType()
		{
			return this->type;
		}
	};
}