#pragma once
class Interface
{
public:
	Interface();
	~Interface();

	void draw(void);
	void update(float deltaTime);

	int crystalWidth, crystalHeight, crystalOffset;
};

