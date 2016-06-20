#pragma once
#include "Vector.h"
#include "Weapon.h"

class Player
{
private:
	static Player* instance;
public:
	Player();
	~Player();

	void setCamera();
	void setPosition(float angle, float fac, bool height);
	void draw(void);

	static Player* getInstance(void);
	static void init(void);

	Vec3f position;
	Vec2f rotation;

	Weapon* leftWeapon;
	Weapon* rightWeapon;

	float health;
	float xp;
	int level;
	int crystals;

	float speed;
};