#pragma once
#include "Header.h"
#include "State.h"

class StateHandler
{
public:
	enum EState { INIT_STATE = 0, LOADING_STATE = 1, MENU_STATE = 2, SETTINGS_STATE = 3, WORLD_STATE = 4 };

	StateHandler();
	~StateHandler();

	void Navigate(EState state);
	State* GetCurrentState();
private:
	EState CurrentState;
	vector<State*> StateList;
};

