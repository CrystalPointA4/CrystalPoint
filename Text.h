#pragma once
#include "MenuElement.h"
#include "Vector.h"
#include "Util.h"

class Text : public MenuElement
{
private:
	std::string text;
	Vec3f color;
public:
	Text(const std::string &text, Vec2f position);
	~Text();

	void draw();
	void update(int x, int y);

	void setColor(Vec3f color);
};

