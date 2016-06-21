#pragma once

class WorldHandler;
class SoundSystem;
class Player;
class Cursor;
class Menu;
#include "Vector.h"
#include "SoundSystem.h"
#include "ControllerHandler.h"

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
	ControllerHandler controller;
	Cursor* cursor;
	Menu* menu;

	static int width, height;
	KeyboardState keyboardState;
	KeyboardState prevKeyboardState;

	Vec2f mouseOffset;
	Vec2f mousePosition;

	float lastFrameTime;

	static SoundSystem& GetSoundSystem() { return sound_system; }
	

private:
	static SoundSystem sound_system;
	void buildMenu();
};