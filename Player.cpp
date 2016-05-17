#include "Player.h"



Player::Player()
{
	right = new Weapon("models/weapons/ZwaardMetTextures/TextureZwaard.obj");
	left = new Weapon("models/weapons/ZwaardMetTextures/TextureZwaard.obj");
}


Player::~Player()
{
	delete right;
	delete left;
}

void Player::Draw_Player(void)
{
	if (right != nullptr)
	{	
		glPushMatrix();
		glTranslatef(2.5f,0,-4.5f);
		right->draw_weapon();		
		glPopMatrix();
	}
		
	if (left != nullptr)
	{
		glPushMatrix();
		glTranslatef(-0.5f,0,-4.5f);
		left->draw_weapon();
		glPopMatrix();

	}

	glRotatef(eyes.rotX, 1, 0, 0);
	glRotatef(eyes.rotY, 0, 1, 0);
	glTranslatef(eyes.posX, eyes.posY, eyes.posZ);
}

