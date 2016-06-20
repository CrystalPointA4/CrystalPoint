#pragma once
#include "Text.h"

class Button : public Text
{
private:	
	float width, height;	
	Vec3f background;
	Vec2f planePosition;
	bool cursorOnButton;
	float alfa;
public:
	Button(const std::string &text, Vec2f position, float width, float height);
	~Button();

	void draw();
	void update(int x, int y);

	void setForeground(Vec3f color);
	void setBackground(Vec3f color);
};

