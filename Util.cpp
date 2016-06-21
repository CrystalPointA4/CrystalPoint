#include "Util.h"
#include "stb_image.h"

Util::Util()
{
	
}


Util::~Util()
{
}

GLuint Util::loadTexture(const std::string &filename)
{
	int width, height, bpp;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgData = stbi_load(filename.c_str(), &width, &height, &bpp, 4);
	GLuint num;
	glGenTextures(1, &num);
	glBindTexture(GL_TEXTURE_2D, num);

	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	stbi_image_free(imgData);
	return num;
}

void Util::glutBitmapString(std::string str, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

int Util::glutTextWidth(const std::string str)
{
	int total = 0;
	for (int i = 0; i < str.size(); i++)
	{
		total += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
	return total;
}

//int Util::glutTextHeight()
//{
//	return glutBitmapHeight(GLUT_BITMAP_HELVETICA_18);
//}

