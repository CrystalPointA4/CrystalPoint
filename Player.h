#pragma once
#include "Vector.h"
#include "Weapon.h"

class Player
{
private:
	static Player* instance;
	void levelUp();
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

	float health, maxHp;
	float xp, maxXp;
	int level;
	int crystals;

	float speed;

	void HpUp(int);
	void HpDown(int);
	void XpUp(int);
};