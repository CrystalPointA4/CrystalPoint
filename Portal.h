#pragma once
#include "Entity.h"
#include <string>

class Portal :
	public Entity
{
public:
	Portal(const std::string &fileName,
		const Vec3f &position,
		Vec3f &rotation,
		const float &scale);
	~Portal();

	void collide();
	int maxCrystals;
	bool mayEnter;
};

