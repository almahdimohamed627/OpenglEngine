#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "globals.h"

class Transformation {
protected:
    static char applaid;
    static bool onX;
    static bool onY;
    static bool onZ;

public:
    static void display();
    static void reset();
    static void toggleX();
    static void toggleY();
    static void toggleZ();
    static void xyz();
    static void set(char transformation);
};

#endif // TRANSFORMATION_H
