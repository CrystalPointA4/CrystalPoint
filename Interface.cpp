#include "Interface.h"
#include <GL\freeglut.h>
#include "CrystalPoint.h"

#include <string>

#include "Player.h"

//Prototype
void glutBitmapString(std::string str, int x, int y);

Interface::Interface()
{
	crystalWidth = 20;
	crystalHeight = 50;
	crystalOffset = 5;
	maxCrystals = 0;
}

Interface::Interface(int maxCrystal)
{
	crystalWidth = 20;
	crystalHeight = 50;
	crystalOffset = 5;
	maxCrystals = maxCrystal;
}


Interface::~Interface()
{
}

void Interface::draw()
{
	Player* player = Player::getInstance();

	//Switch view to Ortho
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 1000, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	
	//Draw interface

	//Health bar
	glBegin(GL_QUADS);
	glColor4f(0,0,0, 1.0);
	glVertex2f(250, 980);
	glVertex2f(250, 965);
	glVertex2f(750, 965);
	glVertex2f(750, 980);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.1f, 0.1f, 1.0);
	glVertex2f(250, 980);
	glVertex2f(250, 965);

	glColor4f(1.0f, 0.5f, 0.5f, 1.0);
	glVertex2f(250 + (player->health / 100 * 500), 965);
	glVertex2f(250 + (player->health / 100 * 500), 980);
	glEnd();

	//XP bar
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 1.0);
	glVertex2f(250, 950);
	glVertex2f(250, 935);
	glVertex2f(750, 935);
	glVertex2f(750, 950);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 0.1f, 1.0);
	glVertex2f(250, 950);
	glVertex2f(250, 935);

	glColor4f(1.0f, 1.0f, 0.5f, 1.0);
	glVertex2f(250 + (player->xp / 100 * 500), 935);
	glVertex2f(250 + (player->xp / 100 * 500), 950);
	glEnd();

	//Text: level
	glColor4f(1.0f, 1.0f, 0.1f, 1.0);
	glutBitmapString("Level: " + std::to_string(player->level), 490, 900);

	for (int i = 0; i < maxCrystals; i++)
	{
		glBegin(GL_QUADS);

		if(i < player->crystals)
			glColor4f(0, 1.0f, 1.0f, 1.0f);
		else
			glColor4f(0, 0.4f, 0.4f, 1.0f);

		glVertex2f(975 - crystalWidth / 2	, crystalOffset*i + crystalHeight*i);
		glVertex2f(975 - crystalWidth		, crystalHeight / 2 + crystalOffset*i + crystalHeight*i);

		if (i < player->crystals)
			glColor4f(0, 0.7f, 0.7f, 1.0f);
		else
			glColor4f(0, 0.2f, 0.2f, 1.0f);

		glVertex2f(975 - crystalWidth / 2	, crystalHeight + crystalOffset*i + crystalHeight*i);
		glVertex2f(975						, crystalHeight / 2 + crystalOffset*i + crystalHeight*i);
		glEnd();
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void Interface::update(float deltaTime)
{

}

void glutBitmapString(std::string str, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}