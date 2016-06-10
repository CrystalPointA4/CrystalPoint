#include "cmath"
#include <GL/freeglut.h>

#include "stb_image.h"
#include "Skybox.h"
#include <string>
#include <iostream>

enum{SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};
GLuint skybox[6];

Skybox::Skybox(const float &size, const std::string &folder)
{
	this->size = size;
	this->folder = folder;

	brightness = 80;
	targetBrightness = 80;
}

Skybox::~Skybox()
{
	glDeleteTextures(6, &skybox[0]);
}

void Skybox::init() 
{
	skybox[SKY_LEFT] = loadTexture(folder + "left.png");
	skybox[SKY_BACK] = loadTexture(folder + "back.png");
	skybox[SKY_RIGHT] = loadTexture(folder + "right.png");
	skybox[SKY_FRONT] = loadTexture(folder + "front.png");
	skybox[SKY_TOP] = loadTexture(folder + "top.png");
	skybox[SKY_BOTTOM] = loadTexture(folder + "bottom.png");
}

void Skybox::draw()
{
	glColor4f(brightness/255, brightness/255, brightness/255, 1);

	bool b1 = glIsEnabled(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);

	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(size / 2, size / 2, size / 2);
		glTexCoord2f(0,1);
		glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(0,0);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glTexCoord2f(1,0);
		glVertex3f(size / 2, -size / 2, size / 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
		//left face
		glTexCoord2f(1,1);
		glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(0,1);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(0,0);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(1,0);
		glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
		//front face
		glTexCoord2f(0, 1);
		glVertex3f(size / 2, size / 2, -size / 2);
		glTexCoord2f(1, 1);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(1, 0);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(0, 0);
		glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
		//right face
		glTexCoord2f(1, 1);
		glVertex3f(size / 2, size / 2, -size / 2);
		glTexCoord2f(0,1);
		glVertex3f(size / 2, size / 2, size / 2);
		glTexCoord2f(0,0);
		glVertex3f(size / 2, -size / 2, size / 2);
		glTexCoord2f(1, 0);
		glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_TOP]);
	glBegin(GL_QUADS);                      //top face
		glTexCoord2f(0,0);
		glVertex3f(size / 2, size / 2, size / 2);
		glTexCoord2f(0,1);
		glVertex3f(-size / 2, size / 2, size / 2);
		glTexCoord2f(1,1);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glTexCoord2f(1,0);
		glVertex3f(size / 2, size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BOTTOM]);
	glBegin(GL_QUADS);
		//bottom face
		glTexCoord2f(0,1);
		glVertex3f(size / 2, -size / 2, size / 2);
		glTexCoord2f(0,0);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glTexCoord2f(1,0);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glTexCoord2f(1,1);
		glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);
	if (!b1)
		glDisable(GL_TEXTURE_2D);
}

void Skybox::update(float deltaTime, int curr, int max)
{
	targetBrightness = 80 + ((255 - 80) / max) * curr;

	if (targetBrightness > brightness)
	{
		brightness += 20 * deltaTime;
	}
}

GLuint Skybox::loadTexture(const std::string & fileName)  //load the filename named texture
{
	int width, height, bpp;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);
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

