#include "LoadingScreen.h"
#include <GL\freeglut.h>
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
	glDisable(GL_TEXTURE_2D);
	
		
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, CrystalPoint::height);
	glVertex2f(CrystalPoint::width, CrystalPoint::height);
	glVertex2f(CrystalPoint::width, 0);
	glEnd();
	
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	
	std::ostringstream oss;

	oss << loading << points << std::endl;

	Util::glutBitmapString(oss.str(),
		CrystalPoint::width / 2 - Util::glutTextWidth(oss.str()),
		CrystalPoint::height / 2 - 7);
	
		
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void LoadingScreen::rise()
{
	points++;
	draw();
}
