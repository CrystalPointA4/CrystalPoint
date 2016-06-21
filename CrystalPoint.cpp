
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
bool state = false;

void CrystalPoint::init()
{
	player = Player::getInstance();
	worldhandler = WorldHandler::getInstance();
	cursor = Cursor::getInstance();

	menu = new Menu();
	buildMenu();

	lastFrameTime = 0;
	state = true;

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

	
	worldhandler->draw();
	
	if(!state)
		menu->draw();

	glutSwapBuffers();
}


void CrystalPoint::update()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	if (keyboardState.keys[27] && !prevKeyboardState.keys[27])
		state = !state;
		
	if (state)
	{
		Player* player = Player::getInstance();

		if (keyboardState.special[GLUT_KEY_LEFT] && !prevKeyboardState.special[GLUT_KEY_LEFT])
			worldhandler->PreviousWorld();
		if (keyboardState.special[GLUT_KEY_RIGHT] && !prevKeyboardState.special[GLUT_KEY_RIGHT])
			worldhandler->NextWorld();
		if (keyboardState.special[GLUT_KEY_UP] && !prevKeyboardState.special[GLUT_KEY_UP])
			player->NextLeftWeapon();
		if (keyboardState.special[GLUT_KEY_DOWN] && !prevKeyboardState.special[GLUT_KEY_DOWN])
			player->PreviousLeftWeapon();
		if (keyboardState.keys[27])
			state = false;

		//testing code
		if (keyboardState.keys['u'])
			player->HpUp(1);
		if (keyboardState.keys['i'])
			player->HpDown(1);
		if (keyboardState.keys['o'])
			player->XpUp(1);

		player->rotation.y += mouseOffset.x / 10.0f;
		player->rotation.x += mouseOffset.y / 10.0f;


		float speed = 10;

		Vec3f oldPosition = player->position;
		if (keyboardState.keys['a']) player->setPosition(0, deltaTime*speed, false);
		if (keyboardState.keys['d']) player->setPosition(180, deltaTime*speed, false);
		if (keyboardState.keys['w']) player->setPosition(90, deltaTime*speed, false);
		if (keyboardState.keys['s']) player->setPosition(270, deltaTime*speed, false);
		if (keyboardState.keys['q']) player->setPosition(1, deltaTime*speed, true);
		if (keyboardState.keys['e']) player->setPosition(-1, deltaTime*speed, true);

		Controller *leftcontroller = controller.getLeftController();
		if (leftcontroller != nullptr) {
			Vec2f *leftControllerJoystick = &leftcontroller->joystick;


			if (leftcontroller->joystickButton) {
				controller.rumble(leftcontroller->controllerId, 100, 100);
			}


			if (leftControllerJoystick->y > 0.3) {
				player->setPosition(270, leftControllerJoystick->y * deltaTime * 2.0f, false);
			}
			else if (leftControllerJoystick->y < -0.3) {
				player->setPosition(90, leftControllerJoystick->y * -1 * deltaTime * 2.0f, false);
			}
			if (leftControllerJoystick->x > 0.3) {
				player->setPosition(180, leftControllerJoystick->x * deltaTime * 2.0f, false);
			}
			else if (leftControllerJoystick->x < -0.3) {
				player->setPosition(0, leftControllerJoystick->x * -1 * deltaTime * 2.0f, false);
			}

			player->leftWeapon->rotateWeapon(Vec3f(leftcontroller->ypr.y + 140, 0, -leftcontroller->ypr.z));

		}
		Controller *rightcontroller = controller.getRightController();
		if(rightcontroller != nullptr){
			Vec2f *rightControllerJoystick = &rightcontroller->joystick;
			if (rightControllerJoystick->y > 0.3 || rightControllerJoystick->y < -0.3) {
				player->rotation.x += rightcontroller->joystick.y/4;
			}

			if (rightControllerJoystick->x > 0.3 || rightControllerJoystick->x < -0.3) {
				player->rotation.y += rightcontroller->joystick.x/4;
			}
            player->rightWeapon->rotateWeapon(Vec3f(rightcontroller->ypr.y + 140, 0, -rightcontroller->ypr.z));
        }

		if (player->rotation.x > 90)
			player->rotation.x = 90;
		if (player->rotation.x < -90)
			player->rotation.x = -90;

		player->position.y = worldhandler->getHeight(player->position.x, player->position.z) + 1.7f;

		if (!worldhandler->isPlayerPositionValid())
			player->position = oldPosition;
		/*else if (player->position.y > oldPosition.y + 1.2)
			player->position = oldPosition;
		*/
		worldhandler->update(deltaTime);
	}	
	else
	{
		menu->update();
		cursor->update(cursor->mousePosition + mouseOffset);
	}


	mouseOffset = Vec2f(0, 0);
	prevKeyboardState = keyboardState;
	glutPostRedisplay();

	sound_system.SetListener(player->position, Vec3f(), Vec3f());
}

void CrystalPoint::buildMenu()
{
	Button* start = new Button("Resume", Vec2f(1920 / 2 - 50, 1080 / 2 - 30), 100, 50);
	auto toWorld = [](Button* b)
	{
		state = true;
	};
	start->addAction(toWorld);
	menu->AddMenuElement(start);


	Button* test = new Button("Exit", Vec2f(1920 / 2 - 50, 1080 / 2 + 30), 100, 50);
	test->addAction([](Button* b)
	{
		exit(0);
	});
	menu->AddMenuElement(test);
	Text* t = new Text("Pause", Vec2f(1920 / 2 - Util::glutTextWidth("Pause") / 2, 1080 / 2 - 75));
	t->setColor(Vec3f(255, 255, 0));
	menu->AddMenuElement(t);
}



KeyboardState::KeyboardState()
{
	memset(keys, 0, sizeof(keys));
	memset(special, 0, sizeof(special));
}
