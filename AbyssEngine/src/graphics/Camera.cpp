#include <iostream>
#include "Camera.h"
#include "../entities/components/PComponent.h"
#include "../entities/components/PComponent.h"
#include "../math/mat4.h"
#include "../math/vec4.h"

namespace abyssengine {
	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
		delete cameraPos;
		delete lookatPos;
		delete cameraOffset;
	}


	Camera::Camera(math::vec3 lookatPos, math::vec3 cameraPos)
	{
		delete this->cameraPos;
		delete this->lookatPos;
		this->cameraPos = new math::vec3(cameraPos);
		this->lookatPos = new math::vec3(lookatPos);
	}

	Camera::Camera(PComponent* target, math::vec3 cameraOffset)
	{
		this->target = target;
		this->cameraOffset = new math::vec3(cameraOffset);
	}

	void Camera::calculateLookat()
	{
		math::vec3 lookatPos;
		math::vec3 cameraPos;

		if (this->target != NULL)
		{
			lookatPos = this->target->position;
		}
		else {
			lookatPos = *(this->lookatPos);
		}

		if (this->cameraOffset != NULL)
		{
			cameraPos = lookatPos + (*cameraOffset);
		}
		else {
			cameraPos = *(this->cameraPos);
		}

		cameraPos = (lookatPos - cameraPos) * zoom + cameraPos;

		cameraPos.x += tilt;

		lookatMatrix = math::mat4::LookAt(cameraPos, lookatPos, math::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::setCameraPos(math::vec3 cameraPos)
	{
		delete this->cameraPos;
		this->cameraPos = new math::vec3(cameraPos);
	}

	void Camera::setLookatPos(math::vec3 lookatPos)
	{
		delete this->lookatPos;
		this->lookatPos = new math::vec3(lookatPos);
	}

	math::vec3 Camera::getCameraPos()
	{
		math::vec3 lookatPos = getLookatPos();
		math::vec3 cameraPos;

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

	math::vec3 Camera::getLookatPos()
	{
		math::vec3 lookatPos;

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

	math::mat4* Camera::getViewMat()
	{
		calculateLookat();
		return new math::mat4((*projectionMatrix) * (*lookatMatrix));
	}

	void Camera::beginFrustumCulling()		// Calculates the normals of each plane of the view frustum.
	{
		math::mat4* viewMat = getViewMat();

		float fov = this->fov;
		float aspect = this->aspectRatio;
		float zNear = this->nearF;
		float zFar = this->farF;

		float hh = tan(fov / 2.0f) * zNear;
		float hw = hh * aspect;

		math::vec3 nw = math::vec3(-hw, hh, 1.0f);
		math::vec3 ne = math::vec3(hw, hh, 1.0f);
		math::vec3 se = math::vec3(hw, -hh, 1.0f);
		math::vec3 sw = math::vec3(-hw, -hh, 1.0f);

		this->top = nw.cross(ne).normalize();
		this->right = ne.cross(se).normalize();
		this->bottom = se.cross(sw).normalize();
		this->left = sw.cross(nw).normalize();


		/*this->top = viewMat->columns[1] + viewMat->columns[3];
		this->bottom = viewMat->columns[3] - viewMat->columns[1];
		this->right = viewMat->columns[0] + viewMat->columns[3];
		this->left = viewMat->columns[3] - viewMat->columns[0];

		this->top = this->top / sqrt(this->top.x * this->top.x + this->top.y * this->top.y + this->top.z * this->top.z);
		this->bottom = this->bottom / sqrt(this->bottom.x * this->bottom.x + this->bottom.y * this->bottom.y + this->bottom.z * this->bottom.z);
		this->right = this->right / sqrt(this->right.x * this->right.x + this->right.y * this->right.y + this->right.z * this->right.z);
		this->left = this->left / sqrt(this->left.x * this->left.x + this->left.y * this->left.y + this->left.z * this->left.z);*/





		/*vec3 cameraPos = getCameraPos();
		vec3 farCenter = cameraPos - (getLookatPos() - cameraPos).normalize() * far;

		float farHeight = 2 * tan(toRadians(fov) / 2) * far;
		float farWidth = farHeight * aspectRatio;

		farTopLeft = farCenter + vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) - vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
		farTopRight = farCenter + vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) + vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
		farBottomLeft = farCenter - vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) - vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);
		farBottomRight = farCenter - vec3(0.0f, 1.0f, 0.0f) * (farHeight*0.5f) + vec3(1.0f, 0.0f, 0.0f) * (farWidth*0.5f);*/

	}

	/*
	// pbase_Plane(): get base of perpendicular from point to a plane
	//    Input:  P = a 3D point
	//            PL = a plane with point V0 and normal n
	//    Output: *B = base point on PL of perpendicular from P
	//    Return: the distance from P to the plane PL
	float
	pbase_Plane( Point P, Plane PL, Point* B)
	{
		float    sb, sn, sd;

		sn = -dot( PL.n, (P - PL.V0));
		sd = dot(PL.n, PL.n);
		sb = sn / sd;

		*B = P + sb * PL.n;
		return d(P, *B);
	}
	*/
	bool Camera::inFrustum(GComponent* gComponent)
	{
		/*bool outside = false;

		GComponent::FrustumInfo frustumInfo = gComponent->getFrustumInfo();
		vec3 center = frustumInfo.center;

		for (unsigned short i = 0; i < 4; i++)
		{
			vec3 v;

			switch (i)
			{
			case 0:
				v = this->top;
				break;
			case 1:
				v = this->bottom;
				break;
			case 2:
				v = this->left;
				break;
			case 3:
				v = this->right;
				break;
			}

			float dot = v.dot(center);

			if (dot >= 0.0f) {
				outside = true;
				break;
			}
		}*/

		return true;
	}

	/*
	int FrustumR::pointInFrustum(Vec3 &p) {

		float pcz,pcx,pcy,aux;

		// compute vector from camera position to p
		Vec3 v = p-camPos;

		// compute and test the Z coordinate
		pcz = v.innerProduct(-Z);
		if (pcz > farD || pcz < nearD)
			return(OUTSIDE);

		// compute and test the Y coordinate
		pcy = v.innerProduct(Y);
		aux = pcz * tang;
		if (pcy > aux || pcy < -aux)
			return(OUTSIDE);

		// compute and test the X coordinate
		pcx = v.innerProduct(X);
		aux = aux * ratio;
		if (pcx > aux || pcx < -aux)
			return(OUTSIDE);

		return(INSIDE);
	}
	*/

	math::mat4* Camera::getProjectionMatrix()
	{
		return projectionMatrix;
	}

	void Camera::setProjectionMatrix(float fov, float aspectRatio, float near, float far)
	{
		this->fov = fov;
		this->aspectRatio = aspectRatio;
		this->nearF = near;
		this->farF = far;

		projectionMatrix = math::mat4::perspective(fov, aspectRatio, near, far);
	}
}