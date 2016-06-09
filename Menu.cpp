#include <GL\freeglut.h>
#include "Menu.h"

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
	glOrtho(0, 1000, 1000, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);


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
