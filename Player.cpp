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
	crystals = 0;

	leftWeapon = new Weapon("models/weapons/ZwaardMetTextures/TextureZwaard.obj", 1, position, rotation, Vec3f(4.5, -8, -1), Vec3f(-2.0f, 6.0f, -2.1f), Vec2f(170, 70), Vec2f(20, -80));
	leftWeapon->rotateWeapon(Vec3f(150, 0, 60));
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

	leftWeapon->rotate(rotation);

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

	leftWeapon->move(position);
}

void Player::draw() {
	leftWeapon->draw();
}