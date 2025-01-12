#include "Button.h"
#include <cstdio>

Button::Button(const std::string &name, double x, double y)
    : name(name), x(x), y(y) {}

bool Button::testCollision() {
    float buttonWidth = 20 + (this->name.length() * 9.0);
    float buttonHight = this->y +30;
    if (mouseX >= this->x && mouseX <= (this->x + buttonWidth) &&
        mouseY <= 800-this->y && mouseY >= 800-buttonHight) {
        return true;
    }
    return false;
}

void Button::display() {
    glColor3ub(44.7, 93.1, 83.5);
    glBegin(GL_QUADS);
    glVertex2f((x - 750) / 750.0, (y - 400) / 400.0);
    glVertex2f((x + 20 + (this->name.length() * 9.0) - 750.0) / 750.0, (y - 400) / 400.0);
    glVertex2f((x + 20 + (this->name.length() * 9.0) - 750.0) / 750.0, (y + 30 - 400) / 400.0);
    glVertex2f((x - 750) / 750.0f, (y + 30 - 400) / 400.0);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f((x - 750) / 750.0, (y - 400) / 400.0);
    glVertex2f((x + 20 + (this->name.length() * 9.0) - 750.0) / 750.0, (y - 400) / 400.0);
    glVertex2f((x + 20 + (this->name.length() * 9.0) - 750.0) / 750.0, (y + 30 - 400) / 400.0);
    glVertex2f((x - 750) / 750.0f, (y + 30 - 400) / 400.0);
    glEnd();

    renderBitmapText((x + 10 - 750) / 750.0, (y + 10 - 400) / 400.0, name.c_str(), GLUT_BITMAP_HELVETICA_18);
}

std::string Button::getName() {
    return name;
}