#pragma once
#include "Entity.h"
#include <string>

class Crystal :
	public Entity
{
public:
	Crystal(const std::string &fileName, const Vec3f &position, Vec3f &rotation, const float &scale);
	~Crystal();

	bool filled;
	void draw();
};

