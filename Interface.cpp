#include "Interface.h"
#include <GL\freeglut.h>
#include "CrystalPoint.h"

#include <string>

#include "Player.h"

//Prototype
void glutBitmapString(std::string str, int x, int y);

Interface::Interface()
{
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

	

	int cw, ch, offset;
	cw = 20;
	ch = 50;
	offset = 5;
	for (int i = 0; i < player->crystals; i++)
	{
		glBegin(GL_QUADS);
		glColor4f(0, 1.0f, 1.0f, 1.0f);
		glVertex2f(975 - cw / 2, offset*i + ch*i);
		glVertex2f(975 - cw    , ch / 2 + offset*i + ch*i);
		glColor4f(0, 0.8f, 0.8f, 1.0f);
		glVertex2f(975 - cw / 2, ch + offset*i + ch*i);
		glVertex2f(975         , ch / 2 + offset*i + ch*i);
		glEnd();
	}
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