#pragma once
#include <string>
#include <GL\freeglut.h>

class Util
{
private:
	Util();
	~Util();
public:
	static GLuint loadTexture(const std::string &filename);
	static inline void glutBitmapString(const std::string str, int x, int y);
};

