#pragma once
#include <string>
 
class Skybox
{
private:
	float size;
	std::string folder;
	float brightness;
	float targetBrightness;
public:
	Skybox(const float &size, const std::string &folder);
	~Skybox();

	void init();
	void draw();
	void update(float deltaTime, int, int);
	GLuint loadTexture(const std::string &fileName);
};
