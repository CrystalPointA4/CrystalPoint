#pragma once

#include "Entity.h"
#include <string>
#include "Vector.h"
#include "CrystalPoint.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string &fileName, const std::string &fileMusic, float damage, float health, const Vec3f &position, const Vec3f &rotation, const float &scale);
	~Enemy();

	Sound* music;

	bool hasTarget;
	Vec3f target;
	float speed,radius;
	float health;
	float damage;
	int xp;
	bool canAttack;
	float lastAttacked;
	bool attack();

	void update(float);
	void draw();

	void inEyeSight(Vec3f &);
	void collide(const Entity *entity);
private:
	int hit_sound_id;
};

