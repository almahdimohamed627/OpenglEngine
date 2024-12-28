#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glut.h>

// Declare global variables as extern
extern double th;
extern double Ex;
extern double Ez;
extern double E;
extern int oldTimeSinceStart;
extern int timeSinceStart;
extern int deltaTime;
extern bool sprinting;
extern bool light;
extern bool lighting;
extern bool rotateScene;
extern GLUquadricObj *a;
extern int mouseX, mouseY;
extern double mouseTh;
#endif // GLOBALS_H