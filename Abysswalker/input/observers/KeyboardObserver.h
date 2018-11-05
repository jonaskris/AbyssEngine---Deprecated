#pragma once
class KeyboardObserver
{
public:
	KeyboardObserver();
	virtual ~KeyboardObserver();
	virtual void notifyKeyEvent(const int& key, const int& scancode, const int& action, const int& mods) = 0;
};
 
