#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"

class Entity;

class World
{
public:
	World();
	~World();


	Player& player;
	std::vector<Entity*> entities;
	std::vector<Enemy*> enemies;
	void draw();
	void update(float elapsedTime);
	bool isPlayerPositionValid();
};

