#include "World.h"
#include <GL/freeglut.h>
#include "Entity.h"
#include "LevelObject.h"
#include "json.h"
#include <fstream>
#include <iostream>

World::World() : player(Player::getInstance())
{

	std::ifstream file("worlds/world1.json");
	if(!file.is_open())
		std::cout<<"Uhoh, can't open file\n";
	json::Value v = json::readJson(file);
	std::cout<<v;
	file.close();
	player.position.x = v["player"]["startposition"][0];
	player.position.y = v["player"]["startposition"][1];
	player.position.z = v["player"]["startposition"][2];


	for (auto object : v["objects"])
	{
		bool hasCollision = true;
		if (!object["collide"].isNull())
			hasCollision = object["collide"].asBool();

		Vec3f rotation(0, 0, 0);
		if(!object["rot"].isNull())
			rotation = Vec3f(object["rot"][0], object["rot"][1], object["rot"][2]);

		float scale = 1;
		if (!object["scale"].isNull())
			scale = object["scale"].asFloat();
		
		Vec3f position(object["pos"][0], object["pos"][1], object["pos"][2]);
		entities.push_back(new LevelObject(object["file"], position, rotation, scale, hasCollision));
	}

	//look up table for the enemies	
	std::vector<std::pair<int, std::string>>enemy_models;
	for (auto enemy_model : v["enemy_models"])
	{		
		int id = -1;
		if (!enemy_model["id"].isNull())
			id = enemy_model["id"].asInt();

		std::string fileName = "";
		if (!enemy_model["file"].isNull())
			fileName = enemy_model["file"].asString();

		enemy_models.push_back(std::pair<int, std::string>(id,fileName));
	}

	for (auto enemy : v["enemy_data"])
	{
		int id = -1;
		if (!enemy["id"].isNull())
			id = enemy["id"];
		for (auto enemy_model : enemy_models)
		{
			if (id == enemy_model.first)
			{				
				Vec3f position(0, 0, 0);
				if (!enemy["pos"].isNull())
					position = Vec3f(enemy["pos"][0], enemy["pos"][1], enemy["pos"][2]);

				Vec3f rotation(0, 0, 0);
				if (!enemy["rot"].isNull())
					rotation = Vec3f(enemy["rot"][0], enemy["rot"][1], enemy["rot"][2]);

				float scale = 1.0f;
				if (!enemy["scale"].isNull())
					scale = enemy["scale"].asFloat();
				
				enemies.push_back(new Enemy(enemy_model.second,position,rotation,scale,true));
			}

		}
		
	}
}


World::~World()
{
}

void World::draw()
{
	player.setCamera();

	float lightPosition[4] = { 0, 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	float lightAmbient[4] = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	glColor3f(0.5f, 0.9f, 0.5f);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-50, 0, -50);
	glVertex3f(-50, 0, 50);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 0, -50);
	glEnd();

	for (auto &enemy : enemies)
		enemy->draw();

	for (auto &entity : entities)
		entity->draw();

	

}

void World::update(float elapsedTime)
{
	for (auto &entity : entities)
		entity->update(elapsedTime);

	for (auto &enemy : enemies)
	{
		if (enemy->position.Distance(player.position) <= enemy->radius)
		{
			enemy->hasTarget = true;
			enemy->target.x = player.position.x;
			enemy->target.z = player.position.z;
		}
		else
			enemy->hasTarget = false;

		enemy->update(elapsedTime);
	}
}

bool World::isPlayerPositionValid()
{
	for (auto e : entities)
	{
		if (e->canCollide && e->inObject(player.position))
			return false;
	}
	return true;
}
