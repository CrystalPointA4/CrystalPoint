#pragma once
#include "Text.h"



class Button : public Text
{
private:	
	typedef void(*action_function)(Button* b);
	float width, height;	
	Vec3f background;
	Vec2f planePosition;
	bool cursorOnButton;
	float alfa;
	action_function action = nullptr;
public:
	Button(const std::string &text, Vec2f position, float width, float height);
	~Button();



	void draw();
	void update(int x, int y);

	void addAction(action_function action);

	void setForeground(Vec3f color);
	void setBackground(Vec3f color);
};

