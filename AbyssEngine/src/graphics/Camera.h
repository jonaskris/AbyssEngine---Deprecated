#pragma once
#include <vector>
#include "../input/observers/MouseScrollObserver.h"
#include "../math/vec3.h"
#include "../math/mat4.h"
#include "../entities/components/gComponent/GComponent.h"

namespace abyssengine {
	class PComponent;
	class Camera : public MouseScrollObserver
	{
	private:
		math::vec3* cameraPos = new math::vec3(0.0f, 0.0f, 1.0f);		// Used when camera position is static, otherwise null.
		math::vec3* lookatPos = new math::vec3(0.0f, 0.0f, 0.0f);		// Used when lookatPos is static, otherwise null.
		math::vec3* cameraOffset = NULL;								// Used when camera position is relative to target, aka when cameraPos is null.
		PComponent* target = NULL;										// Used when camera is to follow a target, aka when lookatPos is null.

		float fov;
		float aspectRatio;
		float nearF;
		float farF;

		float zoom = 0;
		float tilt = 0;

		math::mat4* projectionMatrix = NULL;
		math::mat4* lookatMatrix = NULL;

		void calculateLookat();
	public:
		Camera();
		~Camera();
		Camera(math::vec3 lookatPos, math::vec3 cameraPos);
		Camera(PComponent* target, math::vec3 cameraOffset);

		math::mat4* getViewMat();

		void setCameraPos(math::vec3 cameraPos);
		void setLookatPos(math::vec3 lookatPos);

		math::vec3 getCameraPos();
		math::vec3 getLookatPos();

		math::mat4* getProjectionMatrix();
		void setProjectionMatrix(float fov, float aspectRatio, float near, float far);

		void beginFrustumCulling();				// Calculates the normals of each plane of the view frustum.
		math::vec3 bottom, top, left, right;

		math::vec3 farTopLeft;
		math::vec3 farTopRight;
		math::vec3 farBottomLeft;
		math::vec3 farBottomRight;

		bool inFrustum(GComponent* gComponent);


		void notifyMouseScrollEvent(const double& xoffset, const double& yoffset);
	};
}