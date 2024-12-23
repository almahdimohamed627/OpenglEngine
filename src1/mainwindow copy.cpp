#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
int k = 0;
int b = 0;
int w = 0;
int a = 0;
int s = 0;
int d = 0;
double r = 0;
double r2 = 0;
bool chairTableOpen = false;
bool doorOpen = false;
double t = -3.14 / 2;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		exit(0);
		break;
	case 'b':
		k++;
        break;
    case 'd':
        d++;
        break;
	case 'w':
		w--;
		break;
	case 's':
		w++;
		break;
	case 'a':
		d--;
		break;
	case 'q':
		s++;
		break;
	case 'z':
		s--;
		break;
	case '.':
		t += 0.05;
		break;
	case ',':
        t-=0.05;
        break;
	case 'h':
		if(chairTableOpen) {
			chairTableOpen = false;
		}
		else{
			chairTableOpen = true;
		}
		break;
	case 'y':
		if (doorOpen)
		{
			doorOpen = false;
		}
		else
		{
			doorOpen = true;
		}
		break;
	default:
		break;
	}
}
void mouse(int key, int stat, int x, int y) {
switch (key)
{
case GLUT_LEFT_BUTTON:
	if(stat) {
		t -= 0.05;
	}
	break;
case GLUT_RIGHT_BUTTON:
	if (stat)
	{
		t += 0.05;
	}
	break;

default:
	break;
}

}
void initChairList() {
	glPushMatrix();
	glNewList(2, GL_COMPILE);
	glColor3ub(0, 150, 100);
	GLUquadric *a = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-5, 0, 0);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 10, -1.7);
	glRotatef(80, 1, -0.1, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-10.9, -5, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
//handle
	glPushMatrix();
	glTranslatef(0, 6, 2);
	glScalef(0.7, 0.6,0.7);
	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 10);
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
	glPopMatrix();

	glTranslatef(0, 0, 10);

	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPopMatrix();




	glPushMatrix();
	glTranslatef(5, 0, 0);
	glPushMatrix();
	glTranslatef(-1.4, 10, -1.7);
	glRotatef(80, 1, 0.1, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
	glPushMatrix();
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
	glTranslatef(0, 0, 10);
	glPushMatrix();
	glRotatef(80, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 10, 100, 100);
	glPopMatrix();
	glPopMatrix();
//wooden stuff
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glPushMatrix();
	glTranslatef(0, 6, -0.4);
	glRotatef(-10, 1, 0, 0);
	glScalef(1.5, 1, 0.1);
	glutSolidCube(7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0.55, 5.5);
	glScalef(1, 0.06, 0.9);
	glutSolidCube(11);
	glPopMatrix();
	glEndList();
	// table
	glNewList(3, GL_COMPILE);
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glPushMatrix();
	glTranslatef(4.52, 0.5, 0);
	glScalef(1, 0.06, 0.6);
	glutSolidCube(11);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.5, -4);
	glScalef(0.4, 0.13, 0.6);
	glutSolidCube(5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glEndList();
	glPopMatrix();
	
}

void drewChair() {
	glPushMatrix();
	if (chairTableOpen)
	{
	if (r < 90)
	{
		r += 2;
	}
	}
	else {
		if(r> 0) {
			r -= 2;
		}
	}
	glCallList(2);
	glTranslatef(-5.2, 6, 7.4);
	glRotatef(r, 0, 0, 1);
	glCallList(3);
	glPopMatrix();
}

void initMeetingChair() {
	glPushMatrix();
	glNewList(4, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(100, 100, 100);
	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	//leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 100, 100);
	glPopMatrix();

	

	glColor3ub(20, 20, 15);
	//base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	//back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	//handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	//seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	

	glEndList();
	glPopMatrix();
}


void initMeetingTable() {
	glPushMatrix();
	glNewList(5, GL_COMPILE);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(60, 45, 15);

	//table
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();

	//leg
	glPushMatrix();
	glTranslatef(0, -1, 0);
	glScalef(0.5, 5, 0.5);
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPopMatrix();

	// base
	glPushMatrix();
	glTranslatef(0, -2, 0);
	glScalef(0.7, 0.5, 0.7);
	glPushMatrix();
	glScalef(1.5, 0.1, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluCylinder(a, 2, 2, 4, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -0.2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.1);
	gluDisk(a, 0, 2, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//square
	glColor3ub(30, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0.08, 0);
	glScalef(1.5, 0.1, 1);
	glutSolidCube(3);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}

void drewMeetingTable() {
	GLUquadric *a = gluNewQuadric();
	glColor3ub(250, 0, 0);
	glPushMatrix();
	glTranslatef(0, 28.5, -30);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, -28);
	glRotatef(-10, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, -29);
	glRotatef(10, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	
	glPushMatrix();
	glTranslatef(60, 28.5, 1);
	glRotatef(-90, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-60, 28.5, 0);
	glRotatef(90, 0, 1, 0);
	glCallList(4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 21, 0);
	glScalef(10, 10, 10);
	glCallList(5);
	glPopMatrix();
	glTranslatef(0, 28.5, 30);
	glRotatef(180, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 28.5, 28);
	glRotatef(191, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-31, 28.5, 29);
	glRotatef(170, 0, 1, 0);
	glCallList(4);
	glPopMatrix();
}

void initDoor() {
	glPushMatrix();
	glNewList(6, GL_COMPILE);
	glColor3ub(255, 0, 0);
	GLUquadric *a = gluNewQuadric();
	glColor3ub(0, 0, 0);
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(1, 2, 0.02);
	glutSolidCube(4);

	glPopMatrix();
	glEndList();

	// doors
	glPushMatrix();
	glNewList(7, GL_COMPILE);
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glTranslatef(2, 0, 0);
	glScalef(1, 2, 0.08);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(110, 110, 110);
	glTranslatef(3.6, 0, -0.5);
	gluCylinder(a, 0.2, 0.2, 1, 100, 100);
	gluDisk(a, 0, 0.2, 100, 100);
	glTranslatef(0, 0, 1);
	gluDisk(a, 0, 0.2, 100, 100);
	glPopMatrix();
	glEndList();
	glPopMatrix();
	glPushMatrix();
	glNewList(8, GL_COMPILE);
	glPushMatrix();
	glColor3ub(110, 100, 20);
	glTranslatef(2, 0, 0);
	glScalef(1, 2, 0.08);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(110, 110, 110);
	glTranslatef(3.6, 0, -0.5);
	gluCylinder(a, 0.2, 0.2, 1, 100, 100);
	gluDisk(a, 0, 0.2, 100, 100);
	glTranslatef(0, 0, 1);
	gluDisk(a, 0, 0.2, 100, 100);
	glPopMatrix();

	glEndList();
	glPopMatrix();
}

void drewDoor() {
	if (doorOpen)
	{
		if (r2 < 90)
		{
			r2 += 2;
		}
	}
	else
	{
		if (r2 > 0)
		{
			r2 -= 2;
		}
	}
	//glRotatef(90, 1, 0, 0);
	glCallList(6);
	glPushMatrix();
	glRotatef(r2, 0, 1, 0);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(r2, 0, -1, 0);
	glCallList(8);
	glPopMatrix();
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	initChairList();
	initMeetingChair();
	initMeetingTable();
	initDoor();
}

void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	//gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void animation(int) {
	glutPostRedisplay();
	glutTimerFunc(16, animation, 0);
	//k++;
}
void DrawGLScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	GLUquadricObj * a = gluNewQuadric();
	
    gluLookAt(d, s, w, d+cos(t), s, w+sin(t), 0, 1, 0);
	

	glPushMatrix();
	for (int i = 0; i < 1; i++)
	{
		glTranslatef(0, 0, -20);
		drewDoor();
	}
	glPopMatrix();



	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE); // Use single display buffer.
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("EMPTY WINDOW");
	InitGL();
	glutReshapeFunc(ReSizeGLScene);
	glutDisplayFunc(DrawGLScene);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	animation(0);
	glutMainLoop();
	return 0;
}
