#include <GL/freeglut.h>

#include "CrystalPoint.h"
#include <stdio.h>
#include "Vector.h"

void configureOpenGL(void);

CrystalPoint* app;

bool justMoved = false;

int main(int argc, char* argv[])
{
	app = new CrystalPoint();
	glutInit(&argc, argv);

	configureOpenGL();

	app->init();

	glutDisplayFunc([]() { app->draw(); } );
	glutIdleFunc([]() { app->update(); } );
	glutReshapeFunc([](int w, int h) { CrystalPoint::width = w; CrystalPoint::height = h; glViewport(0, 0, w, h); });

	//Keyboard
	glutKeyboardFunc([](unsigned char c, int, int) { app->keyboardState.keys[c] = true; });
	glutKeyboardUpFunc([](unsigned char c, int, int) { app->keyboardState.keys[c] = false; });
	glutSpecialFunc([](int c, int, int) { app->keyboardState.special[c] = true; });
	glutSpecialUpFunc([](int c, int, int) { app->keyboardState.special[c] = false; });
	
	auto mousemotion = [](int x, int y)
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
			app->mouseOffset = app->mouseOffset + Vec2f(dx, dy);
			glutWarpPointer(app->width / 2, app->height / 2);
			justMoved = true;
		}
	};

	//Mouse
	glutPassiveMotionFunc(mousemotion);
	glutMotionFunc(mousemotion);

	CrystalPoint::height = GLUT_WINDOW_HEIGHT;
	CrystalPoint::width = GLUT_WINDOW_WIDTH;

	glutMainLoop();

	delete app;
	return 0;
}

void configureOpenGL()
{
	//Init window and glut display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	//glutInitWindowPosition(glutGet(GLUT_WINDOW_WIDTH) / 2 - 800/2, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 600/2);
	glutCreateWindow("Crystal Point");	
	glutFullScreen();

	//Depth testing
	glEnable(GL_DEPTH_TEST);

	//Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Alpha testing
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	//Lighting
	GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 0 };
	//GLfloat mat_shininess[] = { 5.0 };
	GLfloat light_position[] = { 0.0, 2.0, 1.0, 0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 0 };
	glClearColor(0.7, 0.7, 1.0, 1.0);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);

	glutSetCursor(GLUT_CURSOR_NONE);
}