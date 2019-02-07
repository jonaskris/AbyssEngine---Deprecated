#pragma once

namespace abyssengine {
	class MouseObserver
	{
	public:
		virtual void notifyMousePositionEvent(const double& xpos, const double& ypos) {};
		virtual void notifyMouseEnterEvent(const int& entered) {};
		virtual void notifyMouseButtonEvent(const int& button, const int& action, const int& mods) {};
		virtual void notifyMouseScrollEvent(const double& xoffset, const double& yoffset) {};
	};
}