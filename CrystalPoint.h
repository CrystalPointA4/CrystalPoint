#pragma once

class WorldHandler;
class Player;
#include "Vector.h"

class KeyboardState
{
public:
	bool keys[256];
	bool special[256];
	bool control, shift, alt;

	KeyboardState();
};

class CrystalPoint
{
public:
	void init();
	void draw();
	void update();

	WorldHandler* worldhandler;
	Player* player;

	static int width, height;
	KeyboardState keyboardState;
	KeyboardState prevKeyboardState;

	Vec2f mouseOffset;
	Vec2f mousePosition;

	float lastFrameTime;

};