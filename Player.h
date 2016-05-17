#pragma once
#include "Header.h"
#include "Weapon.h"

class Player
{
public:
	Player();
	~Player();

	struct Eyes
	{
		float posX = 0;
		float posY = 0;
		float posZ = 0;
		float rotX = 0;
		float rotY = 0;
	} eyes;	

	void Draw_Player(void);
private:
	int level;
	int xp;
	Weapon* right = nullptr;
	Weapon* left = nullptr;
	vector<Weapon> weapons;
};

