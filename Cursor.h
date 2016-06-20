#pragma once
#include "Vector.h"

class Cursor
{
private:
	Cursor();

	static Cursor* instance;
	bool enabled;
	
public:
	Vec2f mousePosition;
	~Cursor();

	static Cursor* getInstance(void);
	
	void enable(bool enable);
	bool isEnabled(void);

	bool clicked;
	int state, prev;


	void draw(void);
	void update(Vec2f newPosition);
};

