#ifndef SPHERE_H
#define SPHERE_H
#include "globals.h"
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere();
    Sphere(int p_id);
    void display() override;
};

#endif
