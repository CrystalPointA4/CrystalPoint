#pragma once
#include "Header.h"

class State
{
public:
	State();
	~State();

	virtual void Entry();
	virtual void Exit();

	virtual void Idle(float delta);
	virtual void Display();

	virtual void Keyboard(bool keys[255]);
	virtual void MouseMove(int x, int y, int dx, int dy);
	virtual void MouseClick(int button, int type, int x, int y);
};

#include "InitState.h"
#include "LoadingState.h"
#include "MenuState.h"
#include "SettingsState.h"
#include "WorldState.h"

