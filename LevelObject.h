#pragma once

#include "Entity.h"
#include <string>


class LevelObject : public Entity
{
public:
	LevelObject(const std::string &fileName, 
		const Vec3f &position, 
		const Vec3f &rotation, 
		const float &scale, 
		const bool &hasCollision);
	~LevelObject();
};

