#pragma once
#include <string>
#include <GL\freeglut.h>

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void draw();
	void rise();
	int points;

	GLuint textureId;
	void setTexture(const std::string fileName);

private:
	const std::string loading = "Loaded: ";

};

