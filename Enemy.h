#pragma once

#include "Entity.h"
#include <string>
#include "Vector.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string &fileName,const Vec3f &position,Vec3f &rotation,const float &scale,const bool &hasCollision);
	~Enemy();

	bool hasTarget;
	Vec3f target;
	float speed,radius;

	void update(float);
	void draw();
};

