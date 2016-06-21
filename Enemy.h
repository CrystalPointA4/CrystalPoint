#pragma once

#include "Entity.h"
#include <string>
#include "Vector.h"
#include "CrystalPoint.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string &fileName, const std::string &fileMusic, const Vec3f &position, const Vec3f &rotation, const float &scale);
	~Enemy();

	Sound* music;

	bool hasTarget;
	Vec3f target;
	float speed,radius;
	bool attack;

	void update(float);
	void draw();

	void inEyeSight(Vec3f &);
	void collide(const Entity *entity);
private:
	int hit_sound_id;
};

