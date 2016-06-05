#pragma once
#include "Vector.h"

class Model;

class Player
{
private:
	static Player* instance;
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

	float health;
	float xp;
	int level;

	float speed;
};