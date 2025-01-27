#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/freeglut.h>

// Declare global variables as extern
extern bool modeList;
extern int ListID;
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
extern bool ctrl_down;
extern bool showingLists;
extern void donothing();

#endif // GLOBALS_H
