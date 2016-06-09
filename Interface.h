#pragma once
class Interface
{
public:
	Interface();
	Interface(int);
	~Interface();

	void draw(void);
	void update(float deltaTime);

	int crystalWidth, crystalHeight, crystalOffset;
	int maxCrystals;
};

