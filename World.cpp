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

	for (auto e : entities)
		e->draw();

}

void World::update(float elapsedTime)
{
	for (auto e : entities)
		e->update(elapsedTime);
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
