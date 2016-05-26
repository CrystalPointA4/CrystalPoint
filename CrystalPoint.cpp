
#include "CrystalPoint.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstring>
#include "WorldHandler.h"
#include "Player.h"

void CrystalPoint::init()
{
	player = Player::getInstance();
	worldhandler = WorldHandler::getInstance();

	lastFrameTime = 0;

	glClearColor(0.7, 0.7, 1.0, 1.0);

	mousePosition = Vec2f(width / 2, height / 2);
}


void CrystalPoint::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw world
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 0.1f, 15000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	worldhandler->draw();
	
	//Draw Cursor
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width, height,0,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1, cos(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), sin(glutGet(GLUT_ELAPSED_TIME) / 1000.0f), 1);

	glBegin(GL_TRIANGLES);
	glVertex2f(mousePosition.x, mousePosition.y);
	glVertex2f(mousePosition.x+15, mousePosition.y+15);
	glVertex2f(mousePosition.x+5, mousePosition.y+20);
	glEnd();

	glutSwapBuffers();
}


void CrystalPoint::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	if (keyboardState.special[GLUT_KEY_LEFT] && !prevKeyboardState.special[GLUT_KEY_LEFT])
		worldhandler->PreviousWorld();
	if (keyboardState.special[GLUT_KEY_RIGHT] && !prevKeyboardState.special[GLUT_KEY_RIGHT])
		worldhandler->NextWorld();
	if (keyboardState.keys[27])
		exit(0);

	Player* player = Player::getInstance();

	player->rotation.y += mouseOffset.x / 10.0f;
	player->rotation.x += mouseOffset.y / 10.0f;
	if (player->rotation.x > 90)
		player->rotation.x = 90;
	if (player->rotation.x < -90)
		player->rotation.x = -90;

	float speed = 2;

	Vec3f oldPosition = player->position;
	if (keyboardState.keys['a']) player->setPosition(0, deltaTime*speed, false);
	if (keyboardState.keys['d']) player->setPosition(180, deltaTime*speed, false);
	if (keyboardState.keys['w']) player->setPosition(90, deltaTime*speed, false);
	if (keyboardState.keys['s']) player->setPosition(270, deltaTime*speed, false);
	//if (keyboardState.keys['q']) player->setPosition(1, deltaTime*speed, true);
	//if (keyboardState.keys['e']) player->setPosition(-1, deltaTime*speed, true);

	if (!worldhandler->isPlayerPositionValid())
		player->position = oldPosition;

	player->position.y = worldhandler->getHeight(player->position.x, player->position.z) + 1.7f;

	worldhandler->update(deltaTime);

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
