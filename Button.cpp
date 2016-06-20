#include "Button.h"
#include <string>
#include "Util.h"
#include "Vector.h"
#include "Cursor.h"

Button::Button(const std::string & text, Vec2f position, float width, float height) : Text(text,position)
{
	this->width = width;
	this->height = height;
	this->planePosition = position;

	cursorOnButton = false;
	alfa = 0.5f;
	background = Vec3f(10, 10, 10);
	//foreground = Vec3f(255, 255, 255);
	this->setColor(Vec3f(255, 255, 255));

	this->position.x += width / 2 - textWidth / 2;
	this->position.y += height / 2 - textHeight / 2;
}

Button::~Button()
{
	/*if (action != nullptr)
		delete action;*/
}

void Button::draw(void)
{
	
	glColor4f(background.x/255.0f, background.y / 255.0f, background.z / 255.0f, alfa);

	glBegin(GL_QUADS);
	glVertex2f(planePosition.x, planePosition.y);
	glVertex2f(planePosition.x, planePosition.y + height);
	glVertex2f(planePosition.x + width, planePosition.y + height);
	glVertex2f(planePosition.x + width, planePosition.y);
	glEnd();	

	/*glColor4f(foreground.x / 255.0f, foreground.y / 255.0f, foreground.z / 255.0f, 1.0f);
	Util::glutBitmapString(text, position.x, position.y+height/2+14/2);*/
	Text::draw();
}

void Button::update(int x, int y)
{	
	cursorOnButton =
		(x > planePosition.x && x < planePosition.x + width) &&
		y > planePosition.y && y < planePosition.y + height;


	if (cursorOnButton)
		alfa = 1.0f;
	else
		alfa = 0.5f;

	if (cursorOnButton && Cursor::getInstance()->clicked)
		if(action != nullptr)
			action(this);
}

void Button::addAction(action_function action)
{
	this->action = action;
}

void Button::setForeground(Vec3f color)
{
	this->setColor(color);
}

void Button::setBackground(Vec3f color)
{
	background = color;
}
