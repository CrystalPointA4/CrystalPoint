#include "WorldHandler.h"
#include "World.h"

#include "json.h"
#include <fstream>
#include <iostream>
#include <string>

WorldHandler* WorldHandler::instance = nullptr;

void WorldHandler::ChangeWorld(int i)
{
	if (i < 0)
		i = worldfiles.size() - 1;

	else if (i >= worldfiles.size())
		i = 0;

	if (i != worldIndex)
	{
		loadingWorld = true;

		if(worldIndex != -1)
			delete world;

		world = new World(worldfiles[i]);
		worldIndex = i;		
		loadingWorld = false;
	}
}

WorldHandler::WorldHandler()
{
	loadingWorld = true;
	worldIndex = -1;

	//Find worlds.json
	std::ifstream file("worlds/worlds.json");
	if (!file.is_open())
		std::cout << "Error, can't open worlds overview file\n";

	json::Value v = json::readJson(file);
	file.close();

	//Load file names into vector
	if (v["worlds"].isNull() || !v["worlds"].isArray())
		std::cout << "Error, no content in worlds overview file\n";

	for (auto line : v["worlds"])
	{
		std::cout << "Found world: " << line << "\n";
		worldfiles.push_back(line);
	}

	if (worldfiles.size() > 0)
	{
		ChangeWorld(0);
	}
}

WorldHandler::~WorldHandler()
{
	worldIndex = -1;
	delete world;
}

WorldHandler* WorldHandler::getInstance()
{
	if (instance == nullptr)
		instance = new WorldHandler();

	return instance;
}

void WorldHandler::init()
{
	instance = new WorldHandler();
}

void WorldHandler::draw(void)
{
	if(!loadingWorld)
		world->draw();
	else
	{
		//Draw Loading screen
	}
}

void WorldHandler::update(float deltaTime)
{
	if(!loadingWorld)
		world->update(deltaTime);
}

bool WorldHandler::isPlayerPositionValid(void)
{
	if(!loadingWorld)
		return world->isPlayerPositionValid();
	return false;
}

float WorldHandler::getHeight(float x, float y)
{
	if (!loadingWorld)
		return world->getHeight(x, y);
	else
		return 0.0f;
}


void WorldHandler::Navigate(const std::string &fileName)
{
	if (!loadingWorld)
	{
		for (int i = 0; i < worldfiles.size(); i++)
		{
			if (worldfiles[i] == fileName)
				ChangeWorld(i);
		}
	}
}

void WorldHandler::NextWorld()
{
	if (!loadingWorld)
	{
		ChangeWorld(worldIndex + 1);
		Player::getInstance()->crystals = 0;
	}
}

void WorldHandler::PreviousWorld()
{
	if (!loadingWorld)
	{
		ChangeWorld(worldIndex - 1);
		Player::getInstance()->crystals = 0;
	}
}