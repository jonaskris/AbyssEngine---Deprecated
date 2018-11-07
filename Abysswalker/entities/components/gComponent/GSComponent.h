#pragma once
#include "GComponent.h"
#include "../../../math/mat4.h"
#include "../PComponent.h"


class GSComponent: public GComponent 
/*	
  |	Graphics sprite component:
  |	All GSC consists of a rectangle described by 4 vertices, 
  | 6 indices (for two triangles creating a rectangle), 
  | a texture, a vec4 describing color tint, and lastly a model-, and world- matrix.
  | The vertices and indices are shared between all GSC.
*/
{
public:
	GSComponent(PComponent* pComponent, unsigned short spriteID);
	~GSComponent();
private:
	mat4 modelMatrix;	// modelMatrix:		The vertices relative to the center of the model
	mat4* worldMatrix;	// worldMatrix:		The vertices relative to the entity's position. The world matrix is found in the PComponent.

	unsigned short spriteID;
	vec4 colorTint;

	static const float vertices[];
	static const unsigned short indices[];
};