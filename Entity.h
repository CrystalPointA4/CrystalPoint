#pragma once

#include "Vector.h"
class Model;

class Entity
{
public:
	Entity();
	~Entity();

	Model* model;

	virtual void draw();
	virtual void update(float elapsedTime) {};
	virtual void collide() {};

	Vec3f position;
	Vec3f rotation;
	float scale;

	bool canCollide;
	bool inObject(const Vec3f &position);
};

