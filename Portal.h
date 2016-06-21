#pragma once
#include "Entity.h"
#include <string>
#include "CrystalPoint.h"

class Portal :
	public Entity
{
public:
	Portal(const std::string &fileName,
		const Vec3f &position,
		Vec3f &rotation,
		const float &scale);
	~Portal();

	bool enter(float deltaTime);

	void collide();
	int maxCrystals;
	bool mayEnter;
private:
	int sound_id;
	Sound* music;
	bool started;
	float delay;
};

