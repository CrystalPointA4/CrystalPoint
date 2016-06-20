#include "Portal.h"
#include "Model.h"
#include <iostream>
#include "Player.h"
#include "WorldHandler.h"

Portal::Portal(const std::string &fileName,
	const Vec3f &position,
	Vec3f &rotation,
	const float &scale)
{
	model = Model::load(fileName);
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = true;

	mayEnter = false;
	maxCrystals = 0;
}


Portal::~Portal()
{
}

void Portal::collide()
{		
	if (maxCrystals == (Player::getInstance()->crystals) && !mayEnter)
	{
		canCollide = false;
		mayEnter = true;
	}
}
