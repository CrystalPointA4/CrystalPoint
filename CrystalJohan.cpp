
#include "CrystalJohan.h"
#include <GL/freeglut.h>
#include "World.h"

void CrystalJohan::init()
{
	world = new World();
	lastFrameTime = 0;

	glClearColor(0.7, 0.7, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

}


void CrystalJohan::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	world->draw();
}


void CrystalJohan::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;
	
	//	if(keyboardState.special[GLUT_KEY_LEFT] && !prevKeyboardState.special[GLUT_KEY_LEFT])
	if (keyboardState.keys[27])
		exit(0);


	world->player.rotation.y += mouseOffset.x/10.0f;
	world->player.rotation.x += mouseOffset.y/10.0f;
	if (world->player.rotation.x > 90)
		world->player.rotation.x = 90;
	if (world->player.rotation.x < -90)
		world->player.rotation.x = -90;


	mouseOffset = Vec2f(0, 0);
	prevKeyboardState = keyboardState;
	glutPostRedisplay();
}



KeyboardState::KeyboardState()
{
	memset(keys, 0, sizeof(keys));
	memset(special, 0, sizeof(special));
}
