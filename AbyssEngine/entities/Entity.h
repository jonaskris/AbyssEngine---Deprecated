#pragma once
#include <vector>
#include <list>
#include "../math/sets/Set.h"
#include "interaction/behaviours/BehaviourMap.h"

class Component;
class GComponent;
class PComponent; 
class SComponent;
class CComponent;

struct Action;
struct Behaviour;
struct Event;

class Entity
{
public:
	~Entity();
	std::vector<GComponent*> getGComponents();
	std::vector<CComponent*> getCComponents();
	PComponent* getPComponent();
	SComponent* getSComponent();

	void preUpdate();					// Used for creating behaviours
	void update(float deltaTime) ;		// Used for updating behaviour and executing actions
protected:
	Entity(std::vector<Component*>& components);
	void setPComponent(PComponent* pComponent);
	void setSComponent(SComponent* sComponent);
	void addGComponent(GComponent* gComponent);
	void addCComponent(CComponent* cComponent);
private:
	void bindPComponent();										// Binding in this context gives CComponents and GComponents a reference to the PComponent of the entity.
	void bindPComponentToGComponent(GComponent* gComponent);
	void bindPComponentToCComponent(CComponent* cComponent);
protected:

	std::list<Event*> asyncEvents;	// Events that are created by keyevents or other asynchronous sources are put here and inserted into events before anything else in preUpdate().
	std::list<Event*> events;
	std::list<Behaviour*> behaviours;
	std::list<Action*> actions;
	BehaviourMap eventToBehaviourMap;


	std::vector<GComponent*> gComponents;
	std::vector<CComponent*> cComponents;
	PComponent* pComponent;
	SComponent* sComponent;
	friend class CComponent;
	friend class GComponent;
};