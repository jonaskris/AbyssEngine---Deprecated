#pragma once
#include <vector>
#include "../input/observers/MouseScrollObserver.h"
#include "../math/vec3.h"
#include "../math/mat4.h"

class PComponent;

class Camera : public MouseScrollObserver
{
private:
	vec3* cameraPos = new vec3(0.0f, 0.0f, 1.0f);		// Used when camera position is static, otherwise null.
	vec3* lookatPos = new vec3(0.0f, 0.0f, 0.0f);		// Used when lookatPos is static, otherwise null.
	vec3* cameraOffset;									// Used when camera position is relative to target, aka when cameraPos is null.
	PComponent* target;									// Used when camera is to follow a target, aka when lookatPos is null.

	float zoom = 0;
	float tilt = 0;

	mat4 lookatMat;

	void calculateLookat();
public:
	Camera();
	~Camera();
	Camera(vec3 lookatPos, vec3 cameraPos);
	Camera(PComponent* target, vec3 cameraOffset);


	mat4 getLookatMat();

	void setCameraPos(vec3 cameraPos);
	void setLookatPos(vec3 lookatPos);

	vec3 getCameraPos();
	vec3 getLookatPos();

	void notifyMouseScrollEvent(const double& xoffset, const double& yoffset);
};