
#include "stb_image.h"
#include "LoadingScreen.h"

#include "CrystalPoint.h"
#include "Util.h"
#include <ostream>

LoadingScreen::LoadingScreen()
{
	points = 0;
}


LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, CrystalPoint::width, CrystalPoint::height, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	
		
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);
	glTexCoord2f(0, 0);
	glVertex2f(0, CrystalPoint::height);
	glTexCoord2f(1, 0);
	glVertex2f(CrystalPoint::width, CrystalPoint::height);
	glTexCoord2f(1, 1);
	glVertex2f(CrystalPoint::width, 0);	
	glEnd();
	
	/*glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	
	std::ostringstream oss;

	oss << loading << points << std::endl;

	Util::glutBitmapString(oss.str(),
		CrystalPoint::width / 2 - Util::glutTextWidth(oss.str()),
		CrystalPoint::height / 2 - 7);*/
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void LoadingScreen::rise()
{
	points++;
	draw();
}

void LoadingScreen::setTexture(const std::string filename)
{
	textureId = Util::loadTexture(filename);
}