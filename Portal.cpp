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

	started = false;
	delay = 0;

	sound_id = CrystalPoint::GetSoundSystem().LoadSound("WAVE/portal.wav", false);
	music = CrystalPoint::GetSoundSystem().GetSound(sound_id);
	music->SetPos(position, Vec3f());

	mayEnter = false;
	maxCrystals = 0;
}


Portal::~Portal()
{
//	Model::unload(model);
	CrystalPoint::GetSoundSystem().UnloadSound(sound_id);
}

void Portal::collide()
{		
	if (maxCrystals == (Player::getInstance()->crystals) && !mayEnter)
	{
		canCollide = false;
		mayEnter = true;
	}
}

bool Portal::enter(float deltaTime)
{
	if (delay > 3 && started)
	{
		delay = 0;
		return true;
	}

	if (delay == 0 && !started)
	{
		music->Play();
		started = true;
	}

	delay += deltaTime;
	return false;
}
