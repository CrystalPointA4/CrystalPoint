#include "Header.h"
#include "Model.h"

//Prototypes
void bindFuncOpenGL(void);
void configureOpenGL(void);
void loadModels(void);

static int Width;
static int Height;

float lastFrameTime = 0;
bool keys[255];

vector<Model*> models;
int currentModel = 0;

struct Camera
{
	float posX = 0;
	float posY = -10;
	float posZ = 0;
	float rotX = 0;
	float rotY = 0;
} camera;

void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)Width / Height, 0.5, 300);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	//Draw here
	models[currentModel]->draw();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void move(float angle, float fac, bool heigth)
{
	if (heigth)
		camera.posY += angle*fac;
	else
	{
		camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
		camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
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
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(Width / 2, Height / 2);
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);

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

	//Depth testing
	glEnable(GL_DEPTH_TEST);

	//Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Alpha testing
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	//Lighting
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
	models.push_back(new Model("models/weapons/ZwaardMetTextures/TextureZwaard.obj"));
}