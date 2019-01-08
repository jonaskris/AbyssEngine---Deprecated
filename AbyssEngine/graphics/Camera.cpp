#include <iostream>
#include "Camera.h"
#include "../entities/components/PComponent.h"
#include "../entities/components/PComponent.h"
#include "../math/mat4.h"
#include "../math/vec4.h"

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

 	lookatMatrix = mat4::LookAt(cameraPos, lookatPos, vec3(0.0f, 1.0f, 0.0f));
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

	cameraPos = (lookatPos - cameraPos) * zoom + cameraPos;

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

mat4* Camera::getViewMat()
{
	calculateLookat();
	return new mat4((*projectionMatrix) * (*lookatMatrix));
}

void Camera::beginFrustumCulling()		// Calculates the normals of each plane of the view frustum.
{

	mat4* viewMat = getViewMat();

	this->bottom = vec3(
		viewMat->columns[1].x + viewMat->columns[3].x,
		viewMat->columns[1].y + viewMat->columns[3].y,
		viewMat->columns[1].z + viewMat->columns[3].z
	);

	this->top = vec3(
		-viewMat->columns[1].x + viewMat->columns[3].x,
		-viewMat->columns[1].y + viewMat->columns[3].y,
		-viewMat->columns[1].z + viewMat->columns[3].z
	);

	this->left = vec3(
		viewMat->columns[0].x + viewMat->columns[3].x,
		viewMat->columns[0].y + viewMat->columns[3].y,
		viewMat->columns[0].z + viewMat->columns[3].z
	);

	this->right = vec3(
		-viewMat->columns[0].x + viewMat->columns[3].x,
		-viewMat->columns[0].y + viewMat->columns[3].y,
		-viewMat->columns[0].z + viewMat->columns[3].z
	);

	/*vec3 cameraPos = getCameraPos();
	vec3 farCenter = cameraPos - (getLookatPos() - cameraPos).normalize() * far;

	float farHeight = 2 * tan(toRadians(fov) / 2) * far;
	float farWidth = farHeight * aspectRatio;

	farTopLeft = farCenter + vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) - vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
	farTopRight = farCenter + vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) + vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
	farBottomLeft = farCenter - vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) - vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
	farBottomRight = farCenter - vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) + vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);*/

}

bool Camera::inFrustum(GComponent* gComponent)
{	
	bool inside[4]{false, false, false, false};
	for (unsigned short i = 0; i < 4; i++)
	{
		vec3 currentAxis;


		switch (i)
		{
		case 0:
			currentAxis = top;
			break;
		case 1:
			currentAxis = bottom;
			break;
		case 2:
			currentAxis = left;
			break;
		case 3:
			currentAxis = right;
			break;
		}

		GComponent::FrustumInfo frustumInfo = gComponent->getFrustumInfo();

		float lengthC = ((currentAxis * (currentAxis.dot(frustumInfo.center) / currentAxis.magnitude())) / currentAxis.magnitude()).dot(currentAxis);
		float lengthC1 = lengthC + frustumInfo.biggestEnclosingRadius;
		float lengthC2 = lengthC - frustumInfo.biggestEnclosingRadius;

		vec3 cameraPos = getCameraPos();
		float projectedCamera = ((currentAxis * (currentAxis.dot(cameraPos) / currentAxis.magnitude())) / currentAxis.magnitude()).dot(currentAxis);

		if (lengthC1 < projectedCamera || lengthC2 < projectedCamera) {
			inside[i] = true;
		}
	}

	return (inside[0] || inside[1] && inside[2] && inside[3]);
}

mat4* Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float near, float far)
{
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->near = near;
	this->far = far;

	projectionMatrix = mat4::perspective(fov, aspectRatio, near, far);
}