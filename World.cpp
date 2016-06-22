#include "World.h"
#include <GL/freeglut.h>
#include "Entity.h"
#include "json.h"
#include "Model.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "WorldHandler.h"

World::World(const std::string &fileName)
{
	nextworld = false;

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
	if(v["world"].isNull() || v["world"]["heightmap"].isNull() || v["world"]["skybox"].isNull())
		std::cout << "Invalid world file: world - " << fileName << "\n";
	if (v["world"]["object-templates"].isNull())
		std::cout << "Invalid world file: object templates - " << fileName << "\n";
	if (v["player"].isNull() || v["player"]["startposition"].isNull())
		std::cout << "Invalid world file: player - " << fileName << "\n";
	if (v["objects"].isNull())
		std::cout << "Invalid world file: objects - " << fileName << "\n";
	if (v["enemies"].isNull())
		std::cout << "Invalid world file: enemies - " << fileName << "\n";
	if (v["crystal"].isNull())
		std::cout << "Invalid world file: crystals - " << fileName << "\n";

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

	//Load skybox
	skybox = new Skybox(15000.0f, v["world"]["skybox"].asString());
	skybox->init();

	//Map different texture to heightmap if available
	if(!v["world"]["texture"].isNull())
		heightmap->SetTexture(v["world"]["texture"].asString());

	//Set player starting position
	player->position.x = v["player"]["startposition"][0].asFloat();
	player->position.z = v["player"]["startposition"][2].asFloat();
	player->position.y = heightmap->GetHeight(player->position.x, player->position.z);

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
		position.y = getHeight(position.x, position.z);

		entities.push_back(new LevelObject(object["file"].asString(), position, rotation, scale, hasCollision));
	}

	maxEnemies = 0;
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

		//Music
		if (e["music"].isNull())
			std::cout << "Invalid world file: enemies music - " << fileName << "\n";

		//Damage
		if (e["damage"].isNull())
			std::cout << "Invalid world file: enemies damage - " << fileName << "\n";

		//Health
		if (e["health"].isNull())
			std::cout << "Invalid world file: enemies health - " << fileName << "\n";

		//Create
		Vec3f position(e["pos"][0].asFloat(), e["pos"][1].asFloat(), e["pos"][2].asFloat());
		position.y = getHeight(position.x, position.z) + 2.0f;

		maxEnemies++;
		enemies.push_back(new Enemy(e["file"].asString(), e["music"].asString(), e["damage"].asFloat(), e["health"].asFloat(), position, rotation, scale));
	}
	maxCrystals = 0;
	if (!v["crystal"].isNull())
	{
		std::string filled = "unknown";
		std::string empty = "unknown";

		if(!v["crystal"]["full texture"].isNull())
			filled = v["crystal"]["full texture"].asString();

		if(!v["crystal"]["empty texture"].isNull())
			empty = v["crystal"]["empty texture"].asString();

		if (!v["crystal"]["instances"].isNull())
		{
			for (auto instance : v["crystal"]["instances"])
			{
				Vec3f position(0, 0, 0);
				Vec3f rotation(0, 0, 0);
				float scale = 1.0f;

				if (!instance["pos"].isNull())
				{
					position.x = instance["pos"][0];
					position.y = instance["pos"][1];
					position.z = instance["pos"][2];
				}
				
				if (!instance["rot"].isNull())
				{
					rotation.x = instance["rot"][0];
					rotation.y = instance["rot"][1];
					rotation.z = instance["rot"][2];
				}

				if (!instance["scale"].isNull())
					scale = instance["scale"].asFloat();

				position.y = getHeight(position.x, position.z);
				maxCrystals++;
				Crystal *c = new Crystal(filled, empty, position, rotation, scale);
								
				entities.push_back(c);
			}
			interface->maxCrystals = maxCrystals;
		}
	}

	if (!v["world"]["music"].isNull())
	{
		sound_id = CrystalPoint::GetSoundSystem().LoadSound(v["world"]["music"].asString().c_str(), true);
		music = CrystalPoint::GetSoundSystem().GetSound(sound_id);
	}

	if (!v["portal"].isNull())
	{
		Vec3f pos(0, 0, 0);
		if (!v["portal"]["pos"].isNull())
			pos = Vec3f(v["portal"]["pos"][0].asFloat(),
				v["portal"]["pos"][1].asFloat(),
				v["portal"]["pos"][2].asFloat());

		pos.y = getHeight(pos.x, pos.z);

		Vec3f rot(0, 0, 0);
		if (!v["portal"]["rot"].isNull())
			pos = Vec3f(v["portal"]["rot"][0].asFloat(),
				v["portal"]["rot"][1].asFloat(),
				v["portal"]["rot"][2].asFloat());

		float scale = 1.0f;
		if (!v["portal"]["scale"].isNull())
			scale = !v["portal"]["scale"].asFloat();

		portal = new Portal(v["portal"]["file"], pos, rot, scale);
		entities.push_back(portal);
		portal->maxCrystals = maxCrystals;
	}
}


World::~World()
{
	delete heightmap;
	music->Stop();
	CrystalPoint::GetSoundSystem().UnloadSound(sound_id);
	delete skybox;	
	delete portal;
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

	GLfloat lightAmbient[] = { 0.05, 0.05, 0.05, 0 };
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	GLfloat mat_specular[] = { 0.15, 0.15, 0.15, 0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	skybox->draw();
	player->draw();

	heightmap->Draw();

	for (auto &enemy : enemies)
		enemy->draw();

	for (auto &entity : entities)
		entity->draw();

	interface->draw();
}

void World::update(float elapsedTime)
{
	if (nextworld)
	{
		WorldHandler::getInstance()->NextWorld();
		return;
	}

	music->SetPos(player->position, Vec3f());

	if (music->IsPlaying() ==  false)
	{
		music->Play();
	}
	for (auto &entity : entities)
		entity->update(elapsedTime);

	int count = 0;
	int remove = false;

	for (auto &enemy : enemies)
	{

		//Al deze code zou in enemy moeten staan
		enemy->inEyeSight(player->position);


		enemy->update(elapsedTime);
		if (enemy->hasTarget)
		{
            if(player->hit)
                enemy->hit(player->leftWeapon->damage);

			for (auto e : entities)
			{
				if (e->canCollide && e->inObject(enemy->position))
				{
					enemy->collide(e);
					break;
				}
			}

			if (enemy->attack)
			{
                player->HpDown(enemy->damage / 2.0f);
			}
		}
		enemy->position.y = getHeight(enemy->position.x, enemy->position.z) + 1.7f;
		
		if (enemy->isDead())
			remove = true;
		if(!remove)
			count++;
	}

	if (remove)
	{
		delete enemies[count];
		player->XpUp(enemies[count]->xp*2);
		enemies.erase(enemies.begin() + count);
		player->HpUp(10);		
	}

	skybox->update(elapsedTime, maxEnemies - enemies.size(), maxEnemies);

	if (portal->mayEnter)
	{
		if (portal->enter(elapsedTime))
			nextworld = true;
	}

    player->hit = false;
		
}

void World::addLevelObject(LevelObject* obj)
{
	entities.push_back(obj);
}

bool World::isPlayerPositionValid()
{
	for (auto &e : entities)
	{
		if (e->canCollide && e->inObject(player->position))
		{
			e->collide();
			return false;
		}
	}
	return true;
}

