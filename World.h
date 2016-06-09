#pragma once

#include <vector>
#include "HeightMap.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelObject.h"
#include "Interface.h"
#include "Crystal.h"
#include "Skybox.h"

class Entity;

class World
{
private:
	std::vector<std::pair<int, std::pair<std::string, bool>>> objecttemplates;

	Player* player;
	HeightMap* heightmap;
	Interface* interface;
	Skybox* skybox;
	
	int music_id;

	std::vector<Entity*> entities;
	std::vector<Enemy*> enemies;
	std::vector<Crystal*> crystals;
public:
	World(const std::string &fileName);
	~World();

	void draw();
	void update(float elapsedTime);
	bool isPlayerPositionValid();
	float getHeight(float x, float y);
	void addLevelObject(LevelObject* obj);
	std::pair<std::string, bool> getObjectFromValue(int i);
	
};

