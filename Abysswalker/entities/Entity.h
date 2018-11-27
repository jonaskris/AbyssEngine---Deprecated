#pragma once
#include <vector>


class Component;
class GComponent;
class PComponent; 
class SComponent;
class CComponent;

class Entity
{
public:
	~Entity();
	std::vector<GComponent*> getGComponents();
	std::vector<CComponent*> getCComponents();
	PComponent* getPComponent();
	SComponent* getSComponent();
	virtual void update() = 0;
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
	std::vector<GComponent*> gComponents;
	std::vector<CComponent*> cComponents;
	PComponent* pComponent;
	SComponent* sComponent;
	friend class CComponent;
	friend class GComponent;
};