#include "Player.h"

Player::Player()
{
	
}


Player::~Player()
{
	if(right != nullptr)
		delete right;
	if(left != nullptr)
		delete left;
	/*if (player != nullptr)
		delete player;*/
}

void Player::Display(void)
{
	if (right != nullptr)
	{			
		right->draw_weapon();		
	}
		
	if (left != nullptr)
	{		
		left->draw_weapon();		
	}

	/*glRotatef(player->eyes.rotX, 1, 0, 0);
	glRotatef(player->eyes.rotY, 0, 1, 0);
	glTranslatef(player->eyes.posX, player->eyes.posY, player->eyes.posZ);*/
	glRotatef(eyes.rotX, 1, 0, 0);
	glRotatef(eyes.rotY, 0, 1, 0);
	glTranslatef(eyes.posX, eyes.posY, eyes.posZ);
}

Player & Player::GetInstance(void)
{
	static Player instance;
	return instance;
}

//Player * Player::GetInstance(void)
//{
//	if (player == nullptr)
//		player = new Player();
//	return player;
//}

void Player::PlayerMoveEyes(float angle, float fac, bool heigth)
{
	//player movement
	
	/*if (heigth)
		player->eyes.posY += angle*fac;
	else
	{
		player->eyes.posX += (float)cos((player->eyes.rotY + angle) / 180 * M_PI) * fac;
		player->eyes.posZ += (float)sin((player->eyes.rotY + angle) / 180 * M_PI) * fac;
	}*/
	if (heigth)
		eyes.posY += angle*fac;
	else
	{
		eyes.posX += (float)cos((eyes.rotY + angle) / 180 * M_PI) * fac;
		eyes.posZ += (float)sin((eyes.rotY + angle) / 180 * M_PI) * fac;
	}
}

void Player::PlayerRotateEyes(int dx, int dy)
{
	eyes.rotY += dx / 10.0f;
	eyes.rotX += dy / 10.0f;
}

