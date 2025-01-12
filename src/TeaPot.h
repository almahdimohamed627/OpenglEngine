#ifndef TEAPOT_H
#define TEAPOT_H
#include "globals.h"
#include "Shape.h"

class TeaPot : public Shape {
public:
    TeaPot();
    TeaPot(double x, double y, double z);
    TeaPot(Entity *p_perant, double x, double y, double z);
    TeaPot(TeaPot *e);
    void display() override;
    std::string getDisplayCode() override;
    TeaPot* clone() override;
};

#endif
