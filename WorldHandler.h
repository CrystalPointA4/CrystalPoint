#pragma once
#include <string>
#include <vector>

class World;

class WorldHandler
{
private:
	WorldHandler();
	static WorldHandler* instance;

	bool loadingWorld;
	World* world;
	int worldIndex;
	void ChangeWorld(int i);
public:
	
	~WorldHandler();

	static WorldHandler* getInstance(void);
	static void init();

	void draw(void);
	void update(float deltaTime);

	bool isPlayerPositionValid(void);
	float getHeight(float x, float y);

	void Navigate(const std::string &fileName);
	void NextWorld();
	void PreviousWorld();

	std::vector<std::string> worldfiles;
};

