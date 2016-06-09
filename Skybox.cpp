#include "cmath"
#include <GL/freeglut.h>

#include "Util.h"
#include "stb_image.h"
#include "Skybox.h"
#include <string>

enum{SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};
GLuint skybox[6];

Skybox::Skybox(const float &size, const std::string &folder)
{
	this->size = size;
	this->folder = folder;
}

Skybox::~Skybox()
{
	glDeleteTextures(6, &skybox[0]);
}

void Skybox::init() 
{
	skybox[SKY_LEFT] = Util::loadTexture(folder + "left.png");
	skybox[SKY_BACK] = Util::loadTexture(folder + "back.png");
	skybox[SKY_RIGHT] = Util::loadTexture(folder + "right.png");
	skybox[SKY_FRONT] = Util::loadTexture(folder + "front.png");
	skybox[SKY_TOP] = Util::loadTexture(folder + "top.png");
	skybox[SKY_BOTTOM] = Util::loadTexture(folder + "bottom.png");
}

void Skybox::draw()
{
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

