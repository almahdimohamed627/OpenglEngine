#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
using namespace std;

double th = 0;
double Ex = 0;
double Ez = 0;
double E = 0;
bool sprinting = false;
bool light = false;
bool lighting = false;
bool rotateScene = false;
int mouseX, mouseY;
double mouseTh;

GLUquadricObj *a = gluNewQuadric();


void mouseButton(int button, int state, int x, int y)
{
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
mouseX = x;
mouseY = y;
mouseTh = th;
}
}

void keyboard(unsigned char key, int x, int y)
{
switch (key)
{
case 27: /* Escape key */
exit(0);
break;
case 'R':
if (rotateScene)
rotateScene = false;
else
rotateScene = true;
break;
case 'l':
if (light)
light = false;
else
light = true;
break;
case 'L':
if (lighting)
lighting = false;
else
lighting = true;
break;
case 'd':
if (sprinting)
{
Ex = Ex - 5 * sin(th);
Ez = Ez + 5 * cos(th);
}
else
{
Ex = Ex - 2 * sin(th);
Ez = Ez + 2 * cos(th);
}
break;
case 'a':
if (sprinting)
{
Ex = Ex + 5 * sin(th);
Ez = Ez - 5 * cos(th);
}
else
{
Ex = Ex + 2 * sin(th);
Ez = Ez - 2 * cos(th);
}
break;
case 'w':
if (sprinting)
{
Ex = Ex + 5 * cos(th);
Ez = Ez + 5 * sin(th);
}
else
{
Ex = Ex + 2 * cos(th);
Ez = Ez + 2 * sin(th);
}
break;
case 's':
if (sprinting)
{
Ex = Ex - 5 * cos(th);
Ez = Ez - 5 * sin(th);
}
else
{
Ex = Ex - 2 * cos(th);
Ez = Ez - 2 * sin(th);
}
break;
default:
break;
}
}

void mouse(int key, int stat, int x, int y)
{
switch (key)
{
case GLUT_RIGHT_BUTTON:
if (stat)
sprinting = false;
else
sprinting = true;
break;
default:
break;
}
}

void mouseMotion(int x, int y)
{
th = (x - mouseX) / 360.0 + mouseTh;
}

void mouseWheel(int wheel, int direction, int x, int y)
{
if (direction > 0) // Scroll up
{
E += 1.0;
}
else if (direction < 0)
{
E -= 1.0;
}
glutPostRedisplay();
}

void InitGL(void)
{
glShadeModel(GL_SMOOTH); // Enable Smooth Shading
glEnable(GL_DEPTH_TEST); // Enables Depth Testing
glDepthFunc(GL_LEQUAL);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_BLEND); // for transperancy
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
GLfloat am[] = {0.4, 0.4, 0.4, 0.5};
glLightfv(GL_LIGHT0, GL_AMBIENT, am);
GLfloat di[] = {0.8, 0.8, 0.8, 0.5};
glLightfv(GL_LIGHT0, GL_DIFFUSE, di);
GLfloat sp[] = {0.9, 0.9, 0.9, 0.5};
glLightfv(GL_LIGHT0, GL_SPECULAR, sp);
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
GLenum error = glGetError();
if (error != GL_NO_ERROR)
{
printf("OpenGL Error: %s\n", gluErrorString(error));
}
glNewList(1, GL_COMPILE);  // create House list
glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 0.80, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.60, 8.70);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-4.50, 1.60, -2.60);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 3.20, 3.50);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 2.40, -2.60);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.60, 3.50);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 2.40, 2.60);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.60, 3.50);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 4.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.60, 8.70);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(-0.20, 2.40, -4.30);
glRotated(0.00, 1, 0, 0);
glRotated(-90.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 4.80, 8.70);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(-0.20, 2.40, 4.30);
glRotated(0.00, 1, 0, 0);
glRotated(-90.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 4.80, 8.70);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-4.50, 1.60, 2.70);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 3.20, 3.50);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-4.50, 4.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.60, 8.80);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(88.00, 57.00, 39.00, 255.00);
glTranslated(-0.20, 5.50, 2.90);
glRotated(-60.00, 1, 0, 0);
glRotated(-90.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.40, 7.00, 9.40);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(88.00, 57.00, 39.00, 255.00);
glTranslated(-0.20, 5.50, -3.00);
glRotated(60.00, 1, 0, 0);
glRotated(-90.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.40, 7.00, 9.40);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-0.30, 4.70, -0.10);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(8.70, 0.30, 7.40);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-4.50, 5.00, 1.20);
glRotated(30.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 2.10, 4.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 5.00, 1.20);
glRotated(30.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 2.10, 4.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(188.00, 159.00, 128.00, 255.00);
glTranslated(-4.50, 5.00, -1.30);
glRotated(150.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 2.10, 4.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(232.00, 220.00, 202.00, 255.00);
glTranslated(4.00, 5.00, -1.30);
glRotated(150.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 2.10, 4.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(80.00, 80.00, 100.00, 255.00);
glTranslated(-4.58, 5.20, -0.02);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.30, 1.00, 1.00);
glutSolidSphere(1, 50, 50);
glPopMatrix();

glEndList();

glNewList(19, GL_COMPILE);  // create TV list
glPushMatrix();
glColor4ub(110.00, 110.00, 110.00, 255.00);
glTranslated(0.00, 0.60, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(1.00, 1.20, 2.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(0.00, 1.60, 0.20);
glRotated(30.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.10, 1.20, 0.10);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(0.00, 1.60, -0.40);
glRotated(-30.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.10, 1.20, 0.10);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(40.00, 40.00, 140.00, 255.00);
glTranslated(-0.50, 0.60, -0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.10, 1.00, 1.80);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(110.00, 110.00, 110.00, 255.00);
glTranslated(0.50, 0.50, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.50, 1.00, 2.00);
glutSolidCube(1);
glPopMatrix();

glEndList();

glNewList(25, GL_COMPILE);  // create Table list
glPushMatrix();
glColor4ub(74.00, 50.00, 27.00, 255.00);
glTranslated(0.00, 1.10, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(3.00, 0.20, 2.00);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(74.00, 50.00, 27.00, 255.00);
glTranslated(-1.40, 0.50, -0.90);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.00, 0.20);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(74.00, 50.00, 27.00, 255.00);
glTranslated(-1.40, 0.50, 0.90);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.00, 0.20);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(74.00, 50.00, 27.00, 255.00);
glTranslated(1.40, 0.50, 0.90);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.00, 0.20);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(74.00, 50.00, 27.00, 255.00);
glTranslated(1.40, 0.50, -0.90);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.20, 1.00, 0.20);
glutSolidCube(1);
glPopMatrix();

glEndList();

glNewList(31, GL_COMPILE);  // create Windmill list
glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(0.00, 2.00, -1.00);
glRotated(20.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.30, 4.40, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(-1.00, 2.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(-20.00, 0, 0, 1);
glScaled(0.30, 4.40, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(1.00, 2.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(20.00, 0, 0, 1);
glScaled(0.30, 4.40, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(0.00, 0.00, 0.00, 255.00);
glTranslated(-0.00, 2.00, 1.00);
glRotated(-20.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.30, 4.40, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(60.00, 60.00, 60.00, 255.00);
glTranslated(-0.00, 4.20, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.30, 1.30, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(60.00, 60.00, 60.00, 255.00);
glTranslated(-0.40, 4.80, -0.40);
glRotated(-90.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(45.00, 0, 0, 1);
glScaled(0.30, 1.60, 0.30);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(110.00, 110.00, 110.00, 255.00);
glTranslated(-1.00, 4.80, -1.00);
glRotated(-1.00, 1, 0, 0);
glRotated(45.00, 0, 1, 0);
glRotated(45.00, 0, 0, 1);
glScaled(-0.40, 4.00, 0.10);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(110.00, 110.00, 110.00, 255.00);
glTranslated(-1.00, 4.80, -1.00);
glRotated(0.00, 1, 0, 0);
glRotated(45.00, 0, 1, 0);
glRotated(-45.00, 0, 0, 1);
glScaled(-0.40, 4.00, 0.10);
glutSolidCube(1);
glPopMatrix();

glPushMatrix();
glColor4ub(200.00, 50.00, 50.00, 255.00);
glTranslated(-0.88, 4.80, -0.91);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(0.40, 0.40, 0.40);
glutSolidSphere(1, 50, 50);
glPopMatrix();

glEndList();

}

void ReSizeGLScene(int w, int h)
{
glViewport(0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void DrawGLScene(void)
{
glClearColor(1, 1, 1, 0.0f);  // set background color to white
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers
glMatrixMode(GL_MODELVIEW); // Ensure we're in the modelview matrix mode
    glLoadIdentity();           // Reset transformations
    GLfloat position[] = {0, 10000, 0, 0}; // Light position
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0); // Camera setup
    if (rotateScene)
{
        glRotated(90, 0, 0, 1); // Rotate the scene if needed
}

glPushMatrix();
glTranslated(0.00, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(1.00, 1.00, 1.00);
glCallList(1);  // call House list
glPopMatrix();

glPushMatrix();
glTranslated(0.00, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(1.00, 1.00, 1.00);
glCallList(0);  // call House list
glPopMatrix();

glPushMatrix();
glTranslated(0.00, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(7.80, 7.80, 7.80);
glCallList(19);  // call TV list
glPopMatrix();

glPushMatrix();
glTranslated(0.00, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(7.80, 7.80, 7.80);
glCallList(18);  // call TV list
glPopMatrix();

glPushMatrix();
glTranslated(-24.20, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(1.00, 1.00, 1.00);
glCallList(25);  // call Table list
glPopMatrix();

glPushMatrix();
glTranslated(-24.20, 0.00, 0.00);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(1.00, 1.00, 1.00);
glCallList(24);  // call Table list
glPopMatrix();

glPushMatrix();
glTranslated(-2.70, 0.00, 26.20);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(3.20, 3.20, 3.20);
glCallList(31);  // call Windmill list
glPopMatrix();

glPushMatrix();
glTranslated(-2.70, 0.00, 26.20);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(3.20, 3.20, 3.20);
glCallList(30);  // call Windmill list
glPopMatrix();

glPushMatrix();
glColor4ub(19.00, 124.00, 37.00, 255.00);
glTranslated(-1.58, -0.10, -4.74);
glRotated(0.00, 1, 0, 0);
glRotated(0.00, 0, 1, 0);
glRotated(0.00, 0, 0, 1);
glScaled(87.70, 0.20, 87.70);
glutSolidCube(1);
glPopMatrix();


glutSwapBuffers(); // Swap buffers to display the rendered content
}

void Timer(int)
{
	glutTimerFunc(16, Timer, 0);
	glutPostRedisplay();
}

void setupprojection()
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, 1.0, 100.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use single display buffer.
	glutInitWindowSize(1500, 800);
	glutCreateWindow("stadium");
	InitGL();
	glutReshapeFunc(ReSizeGLScene);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton);				   // For mouse button presses
	glutMotionFunc(mouseMotion);			   // For mouse dragging (motion while holding a button)
	glutMouseWheelFunc(mouseWheel);
	Timer(0);
	glutDisplayFunc(DrawGLScene);
	setupprojection();
	glutMainLoop();
	return 0;
}


