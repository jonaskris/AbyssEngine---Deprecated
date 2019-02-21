#pragma once
#include <iostream>

namespace abyssengine {

	//! Wrapper to restrict instantiation of Action/DataAction to component classes
	struct Collision_Component;
	struct Position_Component;
	struct Graphics_Component;
	class EntityManager;
	struct Behaviour;

	class ActionWrapper {
		virtual ~ActionWrapper() = 0;
		friend struct Collision_Component;
		friend struct Position_Component;
		friend struct Graphics_Component;
		friend struct Behaviour;
		friend class EntityManager;

	public:
		//! Base of all actions, specializations are described in components
		struct Action
		{

		};

	private:
		template<typename Types>
		struct TypeAction : Action
		{
			Types type;

			Types getType()
			{
				return type;
			}
		};

		//! Base of all actions that require data, specializations are described in components
		template<typename Types, typename Data>
		struct DataAction : TypeAction<Types>
		{
			Data data;

			DataAction(Data data)
			{
				this->data = data;
			}

			Data getData()
			{
				return data;
			}
		};
	};
}