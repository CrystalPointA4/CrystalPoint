#pragma once
#include "Vector.h"

class Cursor
{
private:
	Cursor();

	static Cursor* instance;
	bool enabled;
	Vec2f mousePosition;
public:
	
	~Cursor();

	static Cursor* getInstance(void);
	
	void enable(bool enable);
	bool isEnabled(void);

	void draw(void);
	void update(Vec2f newPosition);
};

