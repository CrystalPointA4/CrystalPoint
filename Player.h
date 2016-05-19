#pragma once

#include "Singleton.h"

#include "vector.h"

class Model;

class Player : public Singleton<Player>
{
public:
	Player();

	void setCamera();

	Vec3f position;
	Vec2f rotation;

	Model* leftWeapon;
	Model* rightWeapon;
};