#ifndef CUBE_H
#define CUBE_H
#include "globals.h"
#include "Shape.h"

class Cube : public Shape {
public:
    Cube();
    Cube(int p_id);
    void display() override;
};

#endif
