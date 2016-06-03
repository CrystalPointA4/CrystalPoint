#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
#include <GL/freeglut.h>

Player* Player::instance = NULL;

Player::Player()
{
	speed = 10;
	health = 50;
	xp = 75;
	level = 10;
}

Player* Player::getInstance()
{
	if (instance == nullptr)
		instance = new Player();

	return instance;
}

void Player::init()
{
	instance = new Player();
}

Player::~Player()
{
	if (leftWeapon)
		delete leftWeapon;

	if (rightWeapon)
		delete rightWeapon;
}

void Player::setCamera()
{
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glTranslatef(-position.x, -position.y, -position.z);

}

void Player::setPosition(float angle, float fac, bool height)
{	
	if (height)
		position.y += angle*fac;
	else
	{
		position.x -= (float)cos((rotation.y + angle) / 180 * M_PI) * fac;
		position.z -= (float)sin((rotation.y + angle) / 180 * M_PI) * fac;
	}
}