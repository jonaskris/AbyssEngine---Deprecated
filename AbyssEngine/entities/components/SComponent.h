#pragma once
#include "Component.h"

class SComponent: public Component
{
public:
	float maxHealth;
	float health;
	float stunTimer;

	SComponent(float maxHealth);
	~SComponent();
};