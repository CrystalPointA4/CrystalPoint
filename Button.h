#pragma once
#include "MenuElement.h"

class Button : public MenuElement
{
private:
	std::string text;
	float width, height;
	Vec3f foreground;
	Vec3f background;
public:
	Button(std::string &text, Vec2f position, float width, float height);
	~Button();

	void draw(void);
	void update(int x, int y);

	void setForeground(Vec3f color);
	void setBackground(Vec3f color);
};

