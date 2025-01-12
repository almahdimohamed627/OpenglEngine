#ifndef BUTTON_H
#define BUTTON_H
#include "globals.h"
#include <string>
#include <GL/freeglut.h>
#include <functional>
#include "bitmap.h"

class Button {
private:
    std::string name;
    double x, y;

public:
    Button(const std::string &name, double x, double y);
    bool testCollision();
    void display();
    std::string getName();
};

#endif
