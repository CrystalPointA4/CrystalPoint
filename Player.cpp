#include "Player.h"
#include <GL/freeglut.h>

Player::Player()
{

}

void Player::setCamera()
{
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glTranslatef(-position.x, -position.y, -position.z);

}
