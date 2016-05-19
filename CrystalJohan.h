#pragma once

class World;
#include "vector.h"

class KeyboardState
{
public:
	bool keys[256];
	bool special[256];
	bool control, shift, alt;

	KeyboardState();
};

class CrystalJohan
{
public:
	void init();
	void draw();
	void update();

	World* world;

	int width, height;
	KeyboardState keyboardState;
	KeyboardState prevKeyboardState;

	Vec2f mouseOffset;

	float lastFrameTime;

};