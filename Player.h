#pragma once
#include "Header.h"
#include "Weapon.h"

class Player
{
public:
	~Player();

	struct Eyes
	{
		float posX = 0;
		float posY = 0;
		float posZ = 0;
		float rotX = 0;
		float rotY = 0;
	} eyes;	

	void Display(void);
	//static Player* GetInstance(void);
	static Player& GetInstance(void);
	

	void PlayerMoveEyes(const float angle, const float fac, const bool heigth);
	void PlayerRotateEyes(const int dx, const int dy);
private:
	int level;
	int xp;
	Weapon* right = nullptr;
	Weapon* left = nullptr;
	vector<Weapon> weapons;
	Player();
	Player(Player const&);
	void operator=(Player const&);

	//static Player* player;
};

