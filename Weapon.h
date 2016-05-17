#pragma once
#include "Header.h"
#include "Model.h"

class Weapon
{
public:	
	Weapon(const string &filename);
	Weapon();
	~Weapon();
	void draw_weapon(void);
private:
	Model *weaponModel = nullptr;
	float scale = 0.5f;	
};

