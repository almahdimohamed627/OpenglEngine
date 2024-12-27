#ifndef BUTTON_H
#define BUTTON_H
#include "globals.h"
#include <string>
#include <GL/glut.h>
#include <functional>
#include "bitmap.h"

class Button {
private:
    std::string text;
    double x, y;

public:
    Button(const std::string &text, double x, double y);
    bool testCollision(std::function<void()> func);
    void display();
};

#endif
