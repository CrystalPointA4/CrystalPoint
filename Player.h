#pragma once
#include "Header.h"
#include "Weapon.h"

class Player
{
public:
	Player();
	~Player();
private:
	int level;
	int xp;
	Weapon rigth;
	Weapon left;
	vector<Weapon> weapons;
};

