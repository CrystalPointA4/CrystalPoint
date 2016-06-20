#include <GL\freeglut.h>
#include "Menu.h"
#include "CrystalPoint.h"

Menu::Menu()
{
	cursor = Cursor::getInstance();
}


Menu::~Menu()
{
}

void Menu::draw(void)
{
	//Switch view to Ortho
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, CrystalPoint::width, CrystalPoint::height, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glColor4f(60/255.0f, 60/255.0f, 60/255.0f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(0,0);
	glVertex2f(0, CrystalPoint::height);
	glVertex2f(CrystalPoint::width, CrystalPoint::height);
	glVertex2f(CrystalPoint::width, 0);
	glEnd();


	for (MenuElement* e : elements)
	{
		e->draw();
	}

	cursor->draw();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void Menu::update()
{
	for (MenuElement* e : elements)
	{
		e->update(cursor->mousePosition.x, cursor->mousePosition.y);
	}
}

void Menu::AddMenuElement(MenuElement * e)
{
	elements.push_back(e);
}
