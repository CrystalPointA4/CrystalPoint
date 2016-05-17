#include "Header.h"
#include "Model.h"
#include "Player.h"

//Prototypes
void bindFuncOpenGL(void);
void configureOpenGL(void);
void loadModels(void);

static int Width;
static int Height;

float lastFrameTime = 0;
bool keys[255];

//vector<Model*> models;
//int currentModel = 0;

Player *player;

void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)Width / Height, 0.5, 300);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*glRotatef(player.eyes.rotX, 1, 0, 0);
	glRotatef(player.eyes.rotY, 0, 1, 0);
	glTranslatef(player.eyes.posX, player.eyes.posY, player.eyes.posZ);

	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(180, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	models[currentModel]->draw();
	glPopMatrix();*/

	//Draw here	
	player->Draw_Player();
	
	glutSolidCube(10.0);

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void move(float angle, float fac, bool heigth)
{
	if (heigth)
		player->eyes.posY += angle*fac;
	else
	{
		player->eyes.posX += (float)cos((player->eyes.rotY + angle) / 180 * M_PI) * fac;
		player->eyes.posZ += (float)sin((player->eyes.rotY + angle) / 180 * M_PI) * fac;
	}
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	float speed = 10;

	if (keys['a']) move(0, deltaTime*speed, false);
	if (keys['d']) move(180, deltaTime*speed, false);
	if (keys['w']) move(90, deltaTime*speed, false);
	if (keys['s']) move(270, deltaTime*speed, false);
	if (keys['q']) move(1, deltaTime*speed, true);
	if (keys['e']) move(-1, deltaTime*speed, true);	

	glutPostRedisplay();
}

void mousemotion(int x, int y)
{
	int dx = x - Width / 2;
	int dy = y - Height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		player->eyes.rotY += dx / 10.0f;
		player->eyes.rotX += dy / 10.0f;
		glutWarpPointer(Width / 2, Height / 2);
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);	
	//std::cout << key << std::endl;
	keys[key] = true;
}

void keyboardup(unsigned char key, int, int)
{
	keys[key] = false;
}

int main(int argc, char* argv[])
{
	//Init GLUT
	glutInit(&argc, argv);

	//Configre OpenGL and FreeGLut
	configureOpenGL();

	//Bind functions
	bindFuncOpenGL();

	//Init models
	loadModels();

	//Start the main loop
	glutMainLoop();
	return 0;
}

void bindFuncOpenGL()
{
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc([](int w, int h) { Width = w; Height= h; glViewport(0, 0, w, h); });

	//Keyboard
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	//glutMouseFunc(mousefunc);

	//Mouse
	//glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousemotion);
	
}

void configureOpenGL()
{
	//Init window and glut display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Crystal Point");
	glutFullScreen();
	//glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH) / 2) - (glutGet(GLUT_WINDOW_WIDTH) / 2), (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (glutGet(GLUT_WINDOW_HEIGHT) / 2));

	//Depth testing
	glEnable(GL_DEPTH_TEST);

	//Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Alpha testing
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	Lighting
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 30.0, 30.0, 30.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Cursor
	glutWarpPointer(Width / 2, Height / 2);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

void loadModels() 
{
	player = new Player();
	//models.push_back(new Model("models/weapons/ZwaardMetTextures/TextureZwaard.obj"));
}