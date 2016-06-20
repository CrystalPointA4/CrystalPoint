#include "Cursor.h"
#include <GL\freeglut.h>
#include <cmath>
#include "CrystalPoint.h"

Cursor* Cursor::instance = NULL;

Cursor::Cursor()
{
	enabled = false;
	mousePosition = Vec2f(CrystalPoint::width / 2, CrystalPoint::height / 2);
	clicked = false;
}

Cursor::~Cursor()
{
}

Cursor* Cursor::getInstance(void)
{
	if (instance == nullptr)
		instance = new Cursor();
	
	return instance;
}

void Cursor::enable(bool enable)
{
	enabled = enable;
}

bool Cursor::isEnabled(void)
{
	return enabled;
}

void Cursor::draw(void)
{
	//Draw Cursor
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, CrystalPoint::width, CrystalPoint::height, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1, cos(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), sin(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), 1);

	glBegin(GL_TRIANGLES);
	glVertex2f(mousePosition.x, mousePosition.y);
	glVertex2f(mousePosition.x + 15, mousePosition.y + 15);
	glVertex2f(mousePosition.x + 5, mousePosition.y + 20);
	glEnd();
}

void Cursor::update(Vec2f newPosition)
{
	if (newPosition.x < 0)
		newPosition.x = 0;

	if (newPosition.y < 0)
		newPosition.y = 0;

	if (newPosition.x > CrystalPoint::width)
		newPosition.x = CrystalPoint::width;

	if (newPosition.y > CrystalPoint::height)
		newPosition.y = CrystalPoint::height;

	mousePosition = newPosition;

	if (clicked)
		clicked = !clicked;
	if (state != prev)
		if(state == GLUT_UP)
			clicked = true;
	prev = state;
}
