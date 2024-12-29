#ifndef SPHERE_H
#define SPHERE_H
#include "globals.h"
#include "Entity.h"

class Sphere : public Entity {
public:
    Sphere();
    void display() override;
};

#endif
