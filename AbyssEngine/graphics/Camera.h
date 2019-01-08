#pragma once
#include <vector>
#include "../input/observers/MouseScrollObserver.h"
#include "../math/vec3.h"
#include "../math/mat4.h"
#include "../entities/components/gComponent/GComponent.h"

class PComponent;

class Camera : public MouseScrollObserver
{
private:
	vec3* cameraPos = new vec3(0.0f, 0.0f, 1.0f);		// Used when camera position is static, otherwise null.
	vec3* lookatPos = new vec3(0.0f, 0.0f, 0.0f);		// Used when lookatPos is static, otherwise null.
	vec3* cameraOffset;									// Used when camera position is relative to target, aka when cameraPos is null.
	PComponent* target;									// Used when camera is to follow a target, aka when lookatPos is null.

	float fov;
	float aspectRatio;
	float near;
	float far;

	float zoom = 0;
	float tilt = 0;

	mat4* projectionMatrix;
	mat4* lookatMatrix;

	void calculateLookat();
public:
	Camera();
	~Camera();
	Camera(vec3 lookatPos, vec3 cameraPos);
	Camera(PComponent* target, vec3 cameraOffset);

	mat4* getViewMat();

	void setCameraPos(vec3 cameraPos);
	void setLookatPos(vec3 lookatPos);

	vec3 getCameraPos();
	vec3 getLookatPos();

	mat4* getProjectionMatrix();
	void setProjectionMatrix(float fov, float aspectRatio, float near, float far);

	void beginFrustumCulling();				// Calculates the normals of each plane of the view frustum.
	vec3 bottom, top, left, right;

	vec3 farTopLeft;
	vec3 farTopRight;
	vec3 farBottomLeft;
	vec3 farBottomRight;

	bool inFrustum(GComponent* gComponent);
	

	void notifyMouseScrollEvent(const double& xoffset, const double& yoffset);
};