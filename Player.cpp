#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
#include <GL/freeglut.h>

Player::Player()
{
	speed = 10;
}

void Player::setCamera()
{
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glTranslatef(-position.x, -position.y, -position.z);

}

void Player::setPosition(float angle, float fac, bool height)
{
	fac *= speed;
	if (height)
		position.y += angle*fac;
	else
	{
		position.x -= (float)cos((rotation.y + angle) / 180 * M_PI) * fac;
		position.z -= (float)sin((rotation.y + angle) / 180 * M_PI) * fac;
	}
}