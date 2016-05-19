#pragma once

#include <vector>
#include "Player.h"

class Entity;

class World
{
public:
	World();
	~World();


	Player& player;
	std::vector<Entity*> entities;

	void draw();
	void update(float elapsedTime);

};

