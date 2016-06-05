#pragma once

#include "Entity.h"
#include <string>
#include "Vector.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string &fileName,const Vec3f &position,Vec3f &rotation,const float &scale);
	~Enemy();

	bool hasTarget;
	Vec3f target;
	float speed,radius;

	void update(float);
	void draw();

	void inEyeSight(Vec3f &);
	bool hasCollison(Vec3f &);

private:
	int hit_sound_id;
};

