#pragma once
#include <vector>
#include "MenuElement.h"
#include "Cursor.h"

class Menu
{
private:
	std::vector<MenuElement*> elements;
	Cursor* cursor;
public:
	Menu();
	~Menu();

	void draw(void);
	void update(void);

	void AddMenuElement(MenuElement* e);
};

