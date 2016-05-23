#pragma once

#include "Singleton.h"

#include "Vector.h"

class Model;

class Player : public Singleton<Player>
{
public:
	Player();

	void setCamera();
	void setPosition(float angle, float fac, bool height);

	Vec3f position;
	Vec2f rotation;

	Model* leftWeapon;
	Model* rightWeapon;


	float speed;
};