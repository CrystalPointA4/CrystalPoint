#include "World.h"
#include <GL/freeglut.h>
#include "Entity.h"

World::World() : player(Player::getInstance())
{
	player.position.y = 1.7;

	//entities.push_back(new LevelObject("tree"));
}


World::~World()
{
}

void World::draw()
{
	player.setCamera();


	glColor3f(0.5f, 0.9f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(-50, 0, -50);
	glVertex3f(-50, 0, 50);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 0, -50);
	glEnd();

	for (auto e : entities)
		e->draw();

	glutSwapBuffers();
}

void World::update(float elapsedTime)
{
	for (auto e : entities)
		e->update(elapsedTime);
}
