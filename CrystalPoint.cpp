
#include "CrystalPoint.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstring>
#include "WorldHandler.h"
#include "Player.h"
#include "Cursor.h"
#include "Menu.h"
#include "Text.h"
#include "Vector.h"
#include "Button.h"

int CrystalPoint::width = 0;
int CrystalPoint::height = 0;

SoundSystem CrystalPoint::sound_system;

void CrystalPoint::init()
{
	player = Player::getInstance();
	worldhandler = WorldHandler::getInstance();
	cursor = Cursor::getInstance();

	menu = new Menu();
	menu->AddMenuElement(new Text("Hello", Vec2f(10, 18)));
	menu->AddMenuElement(new Button("Start", Vec2f(1920 / 2, 1080 / 2), 100, 50));

	lastFrameTime = 0;

	glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
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

	//worldhandler->draw();
	menu->draw();

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

	float speed = 10;

	Vec3f oldPosition = player->position;
	if (keyboardState.keys['a']) player->setPosition(0, deltaTime*speed, false);
	if (keyboardState.keys['d']) player->setPosition(180, deltaTime*speed, false);
	if (keyboardState.keys['w']) player->setPosition(90, deltaTime*speed, false);
	if (keyboardState.keys['s']) player->setPosition(270, deltaTime*speed, false);
	if (keyboardState.keys['q']) player->setPosition(1, deltaTime*speed, true);
	if (keyboardState.keys['e']) player->setPosition(-1, deltaTime*speed, true);

	if (!worldhandler->isPlayerPositionValid())
		player->position = oldPosition;

	player->position.y = worldhandler->getHeight(player->position.x, player->position.z) + 1.7f;

	worldhandler->update(deltaTime);

	cursor->update(cursor->mousePosition + mouseOffset);
	menu->update();

	mouseOffset = Vec2f(0, 0);
	prevKeyboardState = keyboardState;
	glutPostRedisplay();

	sound_system.SetListener(player->position, Vec3f(), Vec3f());
}



KeyboardState::KeyboardState()
{
	memset(keys, 0, sizeof(keys));
	memset(special, 0, sizeof(special));
}
