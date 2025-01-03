#include "globals.h"

// Define global variables
 bool modeList = false;
 int ListID = -1;
double th = 0;
double Ex = 0;
double Ez = 0;
double E = 0;
int oldTimeSinceStart = 0;
int timeSinceStart = 0;
int deltaTime = 0;
bool sprinting = false;
bool light = false;
bool lighting = false;
bool rotateScene = false;
GLUquadricObj *a = gluNewQuadric();
int mouseX = 0, mouseY = 0;
double mouseTh =0;
bool ctrl_down = false;
void donothing() {
    return;
}