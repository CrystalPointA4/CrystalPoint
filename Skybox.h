#pragma once
#include <string>
 
class Skybox
{
public:
	Skybox(const float &size);
	~Skybox();

	float size;

	void init();
	void draw();
	GLuint loadTexture(const std::string &fileName);
};
