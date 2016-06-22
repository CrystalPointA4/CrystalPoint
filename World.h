#pragma once

#include <vector>
#include "HeightMap.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelObject.h"
#include "Interface.h"
#include "Crystal.h"
#include "Skybox.h"
#include "CrystalPoint.h"
#include "Portal.h"

class Entity;

class World
{
private:
	std::vector<std::pair<int, std::pair<std::string, bool>>> objecttemplates;
	Sound* music;

	Player* player;
	HeightMap* heightmap;
	Interface* interface;
	Skybox* skybox;
	Portal* portal;

	bool nextworld;
	
	int sound_id,maxCrystals,maxEnemies;

	std::vector<Entity*> entities;
	std::vector<Enemy*> enemies;
	//std::vector<Crystal*> crystals;
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

