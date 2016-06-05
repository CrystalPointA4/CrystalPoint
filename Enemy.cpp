#define _USE_MATH_DEFINES
#include <cmath>
#include "Enemy.h"
#include "Model.h"
#include "CrystalPoint.h"
#include <iostream>

Enemy::Enemy(const std::string &fileName,
	const Vec3f &position,
	Vec3f &rotation,
	const float &scale)
{
	model = Model::load(fileName);
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = true;
	target = position;
	speed = 1;
	radius = 10;
	hasTarget = false;
	hit_sound_id = CrystalPoint::GetSoundSystem().LoadSound("WAVE/Sound.wav", false);
}


Enemy::~Enemy()
{
	if (model)
		Model::unload(model);
}

void Enemy::draw()
{
	Entity::draw();
	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		//convert degrees into radians
		float degInRad = i*(M_PI / 180.0);
		glVertex3f(cos(degInRad)*radius, 1*scale,sin(degInRad)*radius);
	}
	glEnd();

	glPopMatrix();
}

void Enemy::inEyeSight(Vec3f & TargetPosition)
{
	if (position.Distance(TargetPosition) <= radius)
	{
		hasTarget = true;
		target = TargetPosition;
	}
	else
		hasTarget = false;
}

bool Enemy::hasCollison(Vec3f &)
{
	return false;
}

void Enemy::update(float delta)
{
	if (hasTarget)
	{

		//just 2d walking
		float dx, dz, length;

		dx = target.x - position.x;
		dz = target.z - position.z;

		length = sqrt(dx*dx + dz*dz);
		if (length > 0.03)
		{
			dx /= length;
			dz /= length;

			dx *= speed*delta;
			dz *= speed*delta;

			position.x += dx;
			position.z += dz;
		}
		rotation.y = atan2f(dx, dz) * 180 / M_PI;		
	}

	if (false)
	{
		Sound* sound = CrystalPoint::GetSoundSystem().GetSound(hit_sound_id);
		sound->SetPos(position, Vec3f());
		sound->Play();
	}
}
