#include <iostream>
#include "Camera.h"
#include "../entities/components/PComponent.h"
#include "../entities/components/PComponent.h"

Camera::Camera()
{

}

Camera::~Camera()
{
	delete cameraPos;
	delete lookatPos;
	delete cameraOffset;
}


Camera::Camera(vec3 lookatPos, vec3 cameraPos)
{
	delete this->cameraPos;
	delete this->lookatPos;
	this->cameraPos = new vec3(cameraPos);
	this->lookatPos = new vec3(lookatPos);
}

Camera::Camera(PComponent* target, vec3 cameraOffset)
{
	this->target = target;
	this->cameraOffset = new vec3(cameraOffset);
}

mat4 Camera::getLookatMat()
{
	calculateLookat();
	return lookatMat;
}

void Camera::calculateLookat()
{
	vec3 lookatPos;
	vec3 cameraPos;

	if (this->target != NULL)
	{
		lookatPos = this->target->position;
	} else {
		lookatPos = *(this->lookatPos);
	}

	if (this->cameraOffset != NULL)
	{
		cameraPos = lookatPos + (*cameraOffset);
	} else {
		cameraPos = *(this->cameraPos);
	}

	cameraPos = (lookatPos - cameraPos) * zoom + cameraPos;

	cameraPos.x += tilt;

 	lookatMat = mat4::LookAt(cameraPos, lookatPos, vec3(0.0f, 1.0f, 0.0f));
}

void Camera::setCameraPos(vec3 cameraPos)
{
	delete this->cameraPos;
	this->cameraPos = new vec3(cameraPos);
}

void Camera::setLookatPos(vec3 lookatPos)
{
	delete this->lookatPos;
	this->lookatPos = new vec3(lookatPos);
}

vec3 Camera::getCameraPos()
{
	vec3 lookatPos = getLookatPos();
	vec3 cameraPos;

	if (this->cameraOffset != NULL)
	{
		cameraPos = lookatPos + (*cameraOffset);
	}
	else {
		cameraPos = *(this->cameraPos);
	}

	cameraPos.x += tilt;

	return cameraPos;
}

vec3 Camera::getLookatPos()
{
	vec3 lookatPos;

	if (this->target != NULL)
	{
		lookatPos = this->target->position;
	}
	else {
		lookatPos = *(this->lookatPos);
	}
	return lookatPos;
}

void Camera::notifyMouseScrollEvent(const double& xoffset, const double& yoffset)
{
	zoom += (float)(yoffset / 10.0f);
	tilt += (float)(xoffset);
}