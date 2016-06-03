#pragma once

#include <vector>
#include "HeightMap.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelObject.h"

class Entity;

class World
{
private:
	std::vector<std::pair<int, std::string>> objecttemplates;
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
	float getHeight(float x, float y);
	void addLevelObject(LevelObject* obj);
	std::string getObjectFromValue(int i);
};

