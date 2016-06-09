#pragma once
#include "Entity.h"
#include <string>

class Crystal :
	public Entity
{
public:
	Crystal(const std::string &filled, const std::string &empty,
		const Vec3f &position, Vec3f &rotation, const float &scale);
	~Crystal();

	bool isFilled;
	void draw();
	void collide();
private:
	std::string filled, empty;
};

