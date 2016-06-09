#include "Text.h"


Text::Text(const std::string &text, Vec2f position) : MenuElement(position)
{
	this->text = text;
	color = Vec3f(50, 150, 150);
}


Text::~Text()
{
}

void Text::draw()
{
	glColor4f(color.x, color.y, color.z, 1.0f);
	Util::glutBitmapString(text, position.x, position.y);
}

void Text::update(int x, int y)
{
	//Do nothing
}

void Text::setColor(Vec3f color)
{
	this->color = color;
}
