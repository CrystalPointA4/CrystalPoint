#include <GL/freeglut.h>

#include "CrystalJohan.h"
#include <stdio.h>
#include "vector.h"

CrystalJohan* app;

bool justMoved = false;

int main(int argc, char* argv[])
{
	app = new CrystalJohan();
	glutInit(&argc, argv);
	//Init window and glut display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Crystal Point");
	glutFullScreen();
	//glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH) / 2) - (glutGet(GLUT_WINDOW_WIDTH) / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (glutGet(GLUT_WINDOW_HEIGHT) / 2));

	app->init();

	glutDisplayFunc([]() { app->draw(); } );
	glutIdleFunc([]() { app->update(); } );
	glutReshapeFunc([](int w, int h) { app->width = w; app->height = h; glViewport(0, 0, w, h); });

	//Keyboard
	glutKeyboardFunc([](unsigned char c, int, int) { app->keyboardState.keys[c] = true; });
	glutKeyboardUpFunc([](unsigned char c, int, int) { app->keyboardState.keys[c] = false; });

	//Mouse
//	glutMouseFunc(mouse);
	glutPassiveMotionFunc([](int x, int y)
	{
		if (justMoved)
		{
			justMoved = false;
			return;
		}
		int dx = x - app->width / 2;
		int dy = y - app->height / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			app->mouseOffset = app->mouseOffset + Vec2f(dx,dy);
			glutWarpPointer(app->width / 2, app->height / 2);
			justMoved = true;
		}
	});

	glutMainLoop();


	return 0;
}