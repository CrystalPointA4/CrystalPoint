
#include "CrystalJohan.h"
#include <GL/freeglut.h>
#include "World.h"

void CrystalJohan::init()
{
	world = new World();
	lastFrameTime = 0;

	glClearColor(0.7, 0.7, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mousePosition = Vec2f(width / 2, height / 2);
}


void CrystalJohan::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw world
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	world->draw();
	
	//Draw Cursor
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width, height,0,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1, cos(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), sin(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(mousePosition.x, mousePosition.y);
	glVertex2f(mousePosition.x+15, mousePosition.y+15);
	glVertex2f(mousePosition.x+5, mousePosition.y+20);

	glEnd();*/



	glutSwapBuffers();


}


void CrystalJohan::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	//	if(keyboardState.special[GLUT_KEY_LEFT] && !prevKeyboardState.special[GLUT_KEY_LEFT])
	if (keyboardState.keys[27])
		exit(0);


	world->player.rotation.y += mouseOffset.x / 10.0f;
	world->player.rotation.x += mouseOffset.y / 10.0f;
	if (world->player.rotation.x > 90)
		world->player.rotation.x = 90;
	if (world->player.rotation.x < -90)
		world->player.rotation.x = -90;


	Vec3f oldPosition = world->player.position;
	if (keyboardState.keys['a']) world->player.setPosition(0, deltaTime, false);
	if (keyboardState.keys['d']) world->player.setPosition(180, deltaTime, false);
	if (keyboardState.keys['w']) world->player.setPosition(90, deltaTime, false);
	if (keyboardState.keys['s']) world->player.setPosition(270, deltaTime, false);
	if (keyboardState.keys['q']) world->player.setPosition(1, deltaTime, true);
	if (keyboardState.keys['e']) world->player.setPosition(-1, deltaTime, true);
	if (!world->isPlayerPositionValid())
		world->player.position = oldPosition;

	world->update(deltaTime);

	mousePosition = mousePosition + mouseOffset;

	mouseOffset = Vec2f(0, 0);
	prevKeyboardState = keyboardState;
	glutPostRedisplay();
}



KeyboardState::KeyboardState()
{
	memset(keys, 0, sizeof(keys));
	memset(special, 0, sizeof(special));
}
