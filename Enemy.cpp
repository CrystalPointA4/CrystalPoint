#define _USE_MATH_DEFINES
#include <cmath>
#include "Enemy.h"
#include "Model.h"
#include <iostream>

Enemy::Enemy(const std::string &fileName,
	const std::string &fileMusic,
	float damage,
	float health,
	const Vec3f &position,
	const Vec3f &rotation,
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

	xp = health;
	this->health = health;
	this->damage = damage;

	hasTarget = false;
	hit_sound_id = CrystalPoint::GetSoundSystem().LoadSound(fileMusic.c_str(), false);
	music = CrystalPoint::GetSoundSystem().GetSound(hit_sound_id);
	attack = false;	
}


Enemy::~Enemy()
{
	music->Stop();
	CrystalPoint::GetSoundSystem().UnloadSound(hit_sound_id);
	if (model)
		Model::unload(model);
}

void Enemy::draw()
{
	Entity::draw();
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

void Enemy::collide(const Entity * entity)
{
	Vec3f difference = position - entity->position; //zou misschien omgedraait moeten worden
	difference.y = 0;
	difference.Normalize();
	difference = difference * (entity->model->radius + 0.01f);
	position.x = difference.x + entity->position.x;
	position.z = difference.z + entity->position.z;
}

void Enemy::update(float delta)
{
	music->SetPos(position, Vec3f());

	if (hasTarget)
	{
		if (music->IsPlaying() == false)
		{
			music->Play();
		}
		//just 2d walking
		float dx, dz, length;

		dx = target.x - position.x;
		dz = target.z - position.z;

		length = sqrt(dx*dx + dz*dz);
		if (length > 1)
		{
			attack = false;

			dx /= length;
			dz /= length;

			dx *= speed*delta;
			dz *= speed*delta;

			position.x += dx;
			position.z += dz;
		}
		else
		{	
			attack = true;
		}
		rotation.y = atan2f(dx, dz) * 180 / M_PI;		
	}
}