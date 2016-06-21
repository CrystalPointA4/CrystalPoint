#pragma once
#include "Vector.h"

class Model;

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

	static Player* getInstance(void);
	static void init(void);

	Vec3f position;
	Vec2f rotation;

	Model* leftWeapon;
	Model* rightWeapon;

	float health, maxHp;
	float xp, maxXp;
	int level;
	int crystals;

	float speed;

	void HpUp(int);
	void HpDown(int);
	void XpUp(int);
};