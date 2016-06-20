#pragma once
#include "Vector.h"
#include <string>

class MenuElement
{
protected:
	bool hover;
	Vec2f position;
public:
	MenuElement(Vec2f position);
	~MenuElement();

	virtual void draw(void) {};
	virtual void update(int x, int y) {};
};

