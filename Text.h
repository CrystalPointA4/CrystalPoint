#pragma once
#include "MenuElement.h"
#include "Vector.h"
#include "Util.h"

class Text : public MenuElement
{
private:
	std::string text;
	Vec3f color;	
protected:
	int textWidth;
	int textHeight;
public:
	Text(const std::string &text, Vec2f position);
	~Text();

	virtual void draw();
	virtual void update(int x, int y);

	void setColor(Vec3f color);
};

