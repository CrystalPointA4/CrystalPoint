#include "StateHandler.h"

StateHandler::StateHandler()
{
	StateList.push_back(new InitState()); //INIT_STATE
	StateList.push_back(new LoadingState()); //LOADING_STATE
	StateList.push_back(new MenuState()); //MENU_STATE
	StateList.push_back(new SettingsState()); //SETTINGS_STATE
	StateList.push_back(new WorldState()); //WORLD_STATE

	//CurrentState = INIT_STATE;
	CurrentState = WORLD_STATE;
}


StateHandler::~StateHandler()
{
}

void StateHandler::Navigate(EState state)
{
	if (CurrentState == state)
		return;

	StateList.at(CurrentState)->Exit();
	CurrentState = state;
	StateList.at(CurrentState)->Entry();
}

State* StateHandler::GetCurrentState()
{
	return StateList.at(CurrentState);
}
