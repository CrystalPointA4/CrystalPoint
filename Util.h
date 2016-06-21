#pragma once
#include <string>
#include <GL/freeglut.h>

class Util
{
private:
	Util();
	~Util();	
public:
	static GLuint loadTexture(const std::string &filename);
	static void glutBitmapString(std::string str, int x, int y);
	static int glutTextWidth(const std::string str);
	//static int glutTextHeight();
};

