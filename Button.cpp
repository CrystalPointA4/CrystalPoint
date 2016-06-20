#include "Button.h"
#include <string>
#include "Util.h"
#include "Vector.h"

Button::Button(const std::string & text, Vec2f position, float width, float height) : MenuElement(position)
{
	this->width = width;
	this->height = height;
	this->text = text;

	background = Vec3f(10, 10, 10);
	foreground = Vec3f(255, 255, 255);
}

Button::~Button()
{
}

void Button::draw(void)
{
	
	glColor4f(background.x/255.0f, background.y / 255.0f, background.z / 255.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(position.x, position.y);
	glVertex2f(position.x, position.y + height);
	glVertex2f(position.x + width, position.y + height);
	glVertex2f(position.x + width, position.y);
	glEnd();	

	glColor4f(foreground.x / 255.0f, foreground.y / 255.0f, foreground.z / 255.0f, 1.0f);
	Util::glutBitmapString(text, position.x, position.y+height/2+18/2);

}

void Button::update(int x, int y)
{
	//Nothing
}

void Button::setForeground(Vec3f color)
{
	foreground = color;
}

void Button::setBackground(Vec3f color)
{
	background = color;
}
