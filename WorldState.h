#pragma once
#include "Header.h"
#include "State.h"
#include "Player.h"

class WorldState : public State
{
public:
	WorldState();
	~WorldState();

	void Keyboard(bool keys[255],float deltaTime);
	void MouseMove(int x, int y, int dx, int dy);
	void Display();
private:
	//Player* player;
};

