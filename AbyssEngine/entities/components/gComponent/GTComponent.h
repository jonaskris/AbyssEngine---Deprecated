#pragma once
#include "GComponent.h"

class GTComponent: public GComponent
{
public:
	GTComponent();
	~GTComponent();

	FrustumInfo getFrustumInfo();
};

