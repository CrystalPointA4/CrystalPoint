#pragma once
#include <string>
 
class Skybox
{
private:
	float size;
	std::string folder;
public:
	Skybox(const float &size, const std::string &folder);
	~Skybox();

	void init();
	void draw();
	GLuint loadTexture(const std::string &fileName);
};
