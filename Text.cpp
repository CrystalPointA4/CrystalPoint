#include "Text.h"


Text::Text(const std::string &text, Vec2f position) : MenuElement(position)
{
	this->text = text;
	color = Vec3f(50, 150, 150);
	textHeight = 14;
	textWidth = Util::glutTextWidth(text);
}


Text::~Text()
{
}

void Text::draw()
{
	glColor4f(color.x/255.0f, color.y/255.0f, color.z/255.0f, 1.0f);
	Util::glutBitmapString(text, position.x-1, position.y+textHeight);
}

void Text::update(int x, int y)
{
	//Do nothing
}

void Text::setColor(Vec3f color)
{
	this->color = color;
}
