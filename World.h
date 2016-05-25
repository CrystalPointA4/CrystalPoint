#pragma once

#include <vector>
#include "HeightMap.h"
#include "Player.h"

class Entity;

class World
{
public:
	World();
	~World();


	Player& player;
	std::vector<Entity*> entities;
	HeightMap* heightmap;

	void draw();
	void update(float elapsedTime);
	bool isPlayerPositionValid();
};

