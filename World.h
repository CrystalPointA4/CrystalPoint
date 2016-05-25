#pragma once

#include <vector>
#include "HeightMap.h"
#include "Player.h"
#include "Enemy.h"

class Entity;

class World
{
public:
	World(const std::string &fileName);
	~World();

	std::vector<Entity*> entities;
	std::vector<Enemy*> enemies;

	Player* player;
	HeightMap* heightmap;

	void draw();
	void update(float elapsedTime);
	bool isPlayerPositionValid();
};

