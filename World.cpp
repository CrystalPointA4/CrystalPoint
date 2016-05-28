#include "World.h"
#include <GL/freeglut.h>
#include "Entity.h"
#include "json.h"
#include "Model.h"
#include "CrystalPoint.h"
#include <fstream>
#include <iostream>

World::World(const std::string &fileName)
{
	//Store player instance
	player = Player::getInstance();

	//Create the interface
	interface = new Interface();

	//Open world json file
	std::ifstream file(fileName);
	if(!file.is_open())
		std::cout<<"Error, can't open world file - " << fileName << "\n";

	json::Value v = json::readJson(file);
	file.close();

	//Check file
	if(v["world"].isNull() || v["world"]["heightmap"].isNull())
		std::cout << "Invalid world file: world - " << fileName << "\n";
	if (v["player"].isNull() || v["player"]["startposition"].isNull())
		std::cout << "Invalid world file: player - " << fileName << "\n";
	if (v["objects"].isNull())
		std::cout << "Invalid world file: objects - " << fileName << "\n";
	if (v["world"]["object-templates"].isNull())
		std::cout << "Invalid world file: object templates - " << fileName << "\n";

	//Load object templates
	for (auto objt : v["world"]["object-templates"])
	{
		//collision
		bool cancollide = true;
		if (!objt["collision"].isNull())
			cancollide = objt["collision"].asBool();

		objecttemplates.push_back(std::pair<int, std::pair<std::string, bool>>(objt["color"], std::pair<std::string, bool>(objt["file"], cancollide)));
	}

	//Generate heightmap for this world
	heightmap = new HeightMap(v["world"]["heightmap"].asString(), this);

	//Map different texture to heightmap if available
	if(!v["world"]["texture"].isNull())
		heightmap->SetTexture(v["world"]["texture"].asString());

	//Set player starting position
	player->position.x = v["player"]["startposition"][0].asFloat();
	player->position.y = v["player"]["startposition"][1].asFloat();
	player->position.z = v["player"]["startposition"][2].asFloat();

	//Load and place objects into world
	for (auto object : v["objects"])
	{
		//Collision
		bool hasCollision = true;
		if (!object["collide"].isNull())
			hasCollision = object["collide"].asBool();

		//Rotation
		Vec3f rotation(0, 0, 0);
		if(!object["rot"].isNull())
			rotation = Vec3f(object["rot"][0].asFloat(), object["rot"][1].asFloat(), object["rot"][2].asFloat());

		//Scale
		float scale = 1;
		if (!object["scale"].isNull())
			scale = object["scale"].asFloat();
		
		//Position
		if (object["pos"].isNull())
			std::cout << "Invalid world file: objects pos - " << fileName << "\n";
		
		//File
		if (object["file"].isNull())
			std::cout << "Invalid world file: objects file - " << fileName << "\n";

		//Create
		Vec3f position(object["pos"][0].asFloat(), object["pos"][1].asFloat(), object["pos"][2].asFloat());
		entities.push_back(new LevelObject(object["file"].asString(), position, rotation, scale, hasCollision));
	}

	//Load and place enemies into world
	for (auto e : v["enemies"])
	{		
		//Rotation
		Vec3f rotation(0, 0, 0);
		if (!e["rot"].isNull())
			rotation = Vec3f(e["rot"][0].asFloat(), e["rot"][1].asFloat(), e["rot"][2].asFloat());

		//Scale
		float scale = 1.0f;
		if (!e["scale"].isNull())
			scale = e["scale"].asFloat();

		//Position
		if (e["pos"].isNull())
			std::cout << "Invalid world file: enemies pos - " << fileName << "\n";

		//File
		if (e["file"].isNull())
			std::cout << "Invalid world file: enemies file - " << fileName << "\n";

		//Create
		Vec3f position(e["pos"][0].asFloat(), e["pos"][1].asFloat(), e["pos"][2].asFloat());
		enemies.push_back(new Enemy(e["file"].asString(), position, rotation, scale));

	}
}


World::~World()
{
	delete heightmap;
}

std::pair<std::string, bool> World::getObjectFromValue(int val)
{
	for (auto i : objecttemplates)
	{
		if (i.first == val)
			return i.second;
	}

	return objecttemplates[0].second;
}

float World::getHeight(float x, float y)
{
	return heightmap->GetHeight(x, y);
}

void World::draw()
{
	player->setCamera();

	float lightPosition[4] = { 0, 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	float lightAmbient[4] = { 0.2, 0.2, 0.2, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	heightmap->Draw();

	for (auto &enemy : enemies)
		enemy->draw();

	for (auto &entity : entities)
		entity->draw();

	interface->draw();
}

void World::update(float elapsedTime)
{
	for (auto &entity : entities)
		entity->update(elapsedTime);

	for (auto &enemy : enemies)
	{

		//Al deze code zou in enemy moeten staan
		if (enemy->position.Distance(player->position) <= enemy->radius)
		{			
			enemy->hasTarget = true;
			enemy->target.x = player->position.x;
			enemy->target.z = player->position.z;
		}
		else
			enemy->hasTarget = false;

		Vec3f oldpos = enemy->position;
		enemy->update(elapsedTime);
		if (enemy->hasTarget)
		{
			for (auto e : entities)
			{
				if (e->canCollide && e->inObject(enemy->position))
				{
					Vec3f difference = e->position - enemy->position; //zou misschien omgedraait moeten worden
					difference.Normalize();
					difference = difference * (e->model->radius + 0.01f);
					enemy->position = e->position + difference;
					break;
				}
			}
		}		
		//tot hier
	}
}

void World::addLevelObject(LevelObject* obj)
{
	entities.push_back(obj);
}

bool World::isPlayerPositionValid()
{
	for (auto e : entities)
	{
		if (e->canCollide && e->inObject(player->position))
			return false;
	}
	return true;
}
