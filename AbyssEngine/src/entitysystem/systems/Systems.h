#pragma once
#include "System.h"
#include "../entitymanager/EachCallable.h"
#include "../components/Components.h"
#include "../events/Events.h"

namespace entitysystem
{

	class EntityManager;

	/*
		Example System that acts on ComponentA and EventA (UnTargeted).
	*/
	class SystemA : public System< ComponentA, EventA >
	{
	public:
		SystemA() {};
	private:
		/*
			Update is called on every update of EntityManager, as long as it is registered in the EntityManager.
		*/
		void update(const double& dt) override
		{

		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			// The UnitGroup will contain the Unit types that the System template was instantiated with.
			ComponentA* a = units.get<ComponentA>().first;
			size_t aSize = units.get<ComponentA>().second;

			EventA& b = units.get<EventA>().first[0];

			for (size_t i = 0; i < aSize; i++)
				if (b.b)
				{
					a[i].x += (float)dt;
					a[i].y += (float)dt;
					a[i].z += (float)dt;
				}
		}
	};

	/*
		Example System that acts on ComponentA and EventB (Targeted).
	*/
	class SystemB : public System< ComponentA, EventB >
	{
	public:
		SystemB() {};
	private:
		void update(const double& dt) override
		{

		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			ComponentA& a = units.get<ComponentA>().first[0];
			EventB& b = units.get<EventB>().first[0];

			if (b.b)
			{
				a.x += (float)dt;
				a.y += (float)dt;
				a.z += (float)dt;
			}
		}
	};

	class SystemC : public System< ComponentA, EventB::optional >
	{
	public:
		SystemC() {};
	private:
		void update(const double& dt) override
		{

		}

		void updateEntity(const double& dt, UnitGroup& units) override
		{
			ComponentA& a = units.get<ComponentA>().first[0];
			ComponentB* b = units.get<ComponentB>().first;
			size_t bs = units.get<ComponentB>().second;

			if (bs == 0 || b->b)
			{
				a.x += (float)dt;
				a.y += (float)dt;
				a.z += (float)dt;
			}
		}
	};
}